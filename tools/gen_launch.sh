#!/bin/bash
# gen_launch.sh: Compile and generate launch.json for XMC or PSoC6 boards
# Usage: ./gen_launch.sh <fqbn> <build_path> <sketch_path> [boards.txt] [gdb_path]
#   <fqbn>        : Fully Qualified Board Name (e.g. infineon:psoc6:CY8CKIT_062S2_AI or arduino-git:xmc:kit_xmc47_relax)
#   <build_path>  : Directory where the .elf file will be placed
#   <sketch_path> : Path to the sketch (.ino) file
#   [boards.txt]  : (Optional) Path to boards.txt (default: inferred based on device)
#   [gdb_path]    : (Optional) Path to GDB executable (default: inferred based on device)

set -e

FQBN_FULL="$1"
BUILD_PATH="$2"
SKETCH_PATH="$3"

if [[ -z "$FQBN_FULL" || -z "$BUILD_PATH" || -z "$SKETCH_PATH" ]]; then
  echo "Usage: $0 <fqbn> <build_path> <sketch_path> [boards.txt] [gdb_path]"
  exit 1
fi

# Get the script directory and package root
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PACKAGE_DIR="$(dirname "$SCRIPT_DIR")"

# Detect device type based on FQBN
if [[ "$FQBN_FULL" == infineon:psoc6:* ]]; then
  DEVICE_TYPE="psoc6"
  BOARDS_TXT="${4:-$PACKAGE_DIR/boards.txt}"
  GDB_PATH="${5:-$HOME/.arduino15/packages/Infineon/tools/arm-none-eabi-gcc/10.3-2021.10/bin/arm-none-eabi-gdb}"
elif [[ "$FQBN_FULL" == arduino-git:xmc:* ]]; then
  DEVICE_TYPE="xmc"
  XMC_DIR="$(dirname "$SCRIPT_DIR")"
  BOARDS_TXT="${4:-$XMC_DIR/boards.txt}"
  GDB_PATH="${5:-$HOME/.arduino15/packages/infineon/tools/arm-none-eabi-gcc/10.3-2021.10/bin/arm-none-eabi-gdb}"
else
  echo "Unsupported device type in FQBN: $FQBN_FULL"
  exit 1
fi

# Extract board name from FQBN
BOARD_NAME=$(echo "$FQBN_FULL" | awk -F: '{print $NF}')

# Compile the sketch
arduino-cli compile -b "${FQBN_FULL}" --build-path "${BUILD_PATH}" "${SKETCH_PATH}" || exit 1

# Parse boards.txt for variant and other parameters
VARIANT=$(grep "^${BOARD_NAME}\.build\.variant=" "$BOARDS_TXT" | cut -d= -f2)
if [[ -z "$VARIANT" ]]; then
  echo "Could not find variant for $BOARD_NAME in $BOARDS_TXT"
  exit 2
fi

if [[ "$DEVICE_TYPE" == "xmc" ]]; then
  BOARD_V=$(grep "^${BOARD_NAME}\.build\.board\.v=" "$BOARDS_TXT" | cut -d= -f2)
  if [[ -z "$BOARD_V" ]]; then
    echo "Could not find board.v for $BOARD_NAME in $BOARDS_TXT"
    exit 2
  fi
  DEVICE="${VARIANT}-${BOARD_V}"
else
  DEVICE="${VARIANT}"
fi

# Find the .elf executable
EXECUTABLE=$(find "${BUILD_PATH}" -maxdepth 1 -type f -name "*.elf" | head -n 1)
if [[ -z "$EXECUTABLE" ]]; then
  echo "No .elf executable found in $BUILD_PATH."
  exit 3
fi

# Create the .vscode directory and generate launch.json
LAUNCH_DIR="$PACKAGE_DIR/.vscode"
if [ ! -d "$LAUNCH_DIR" ]; then
  mkdir -p "$LAUNCH_DIR"
fi
if [ -f "$LAUNCH_DIR/launch.json" ]; then
  rm "$LAUNCH_DIR/launch.json"
fi

if [[ "$DEVICE_TYPE" == "psoc6" ]]; then
  # Generate launch.json for PSoC6
  cat > "$LAUNCH_DIR/launch.json" <<EOF
{
  "version": "0.2.0",
  "configurations": [
    {
    
      "name": "Cortex-Debug: Debug ${DEVICE} CM4",
      "type": "cortex-debug",
      "request": "launch",
      "servertype": "openocd",
      "device": "${DEVICE}",
      "executable": "${EXECUTABLE}",
      "cwd": "\${workspaceFolder}",
      "interface": "swd",
      "gdbPath": "${GDB_PATH}",
      "showDevDebugOutput": "vscode",
      "configFiles": [
        "$HOME/.arduino15/packages/infineon/tools/openocd/5.2.1.3248/scripts/interface/kitprog3.cfg",
        "$HOME/.arduino15/packages/infineon/tools/openocd/5.2.1.3248/scripts/target/psoc6_2m.cfg"
      ],
      "overrideLaunchCommands": [
        "set mem inaccessible-by-default off",
        "-enable-pretty-printing",
        "set remotetimeout 15",
        "monitor reset run",
        "monitor psoc6 reset_halt sysresetreq"
      ],
      "numberOfProcessors": 2,
      "targetProcessor": 1,// Set to 0 for the CM0+, set to 1 for the CM4
      "postStartSessionCommands": [
        "continue"
      ],
      "overrideRestartCommands": [
        "starti"
      ],
      "postRestartSessionCommands": [],
      "breakAfterReset": true
    }
  ]
}
EOF
else
  # Generate launch.json for XMC
  cat > "$LAUNCH_DIR/launch.json" <<EOF
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Cortex-Debug: Debug ${DEVICE}",
      "type": "cortex-debug",
      "request": "launch",
      "servertype": "jlink",
      "device": "${DEVICE}",
      "executable": "${EXECUTABLE}",
      "cwd": "\${workspaceFolder}",
      "interface": "swd",
      "gdbPath": "${GDB_PATH}",
      "showDevDebugOutput": "vscode"
    }
  ]
}
EOF
fi

echo "launch.json generated for ${DEVICE_TYPE} device ${DEVICE} at $LAUNCH_DIR."
echo "(Using boards.txt at $BOARDS_TXT)"


