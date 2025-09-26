#!/bin/bash
# gen_launch.sh: Compile and generate launch.json for XMC boards
# Usage: ./gen_launch.sh <fqbn> <build_path> <sketch_path> [boards.txt] [gdb_path]
#   <fqbn>        : Fully Qualified Board Name (e.g. arduino-git:xmc:kit_xmc47_relax)
#   <build_path>  : Directory where the .elf file will be placed
#   <sketch_path> : Path to the sketch (.ino) file
#   [boards.txt]  : (Optional) Path to boards.txt (default: $HOME/Arduino/hardware/arduino-git/xmc/boards.txt)
#   [gdb_path]    : (Optional) Path to GDB executable (default: $HOME/.arduino15/packages/Infineon/tools/arm-none-eabi-gcc/10.3-2021.10/bin/arm-none-eabi-gdb)
# Example: ./gen_launch.sh arduino-git:xmc:kit_xmc47_relax ~/output ~/build/Blink.ino ~/Arduino/hardware/arduino-git/xmc/boards.txt /usr/bin/arm-none-eabi-gdb

set -e



FQBN_FULL="$1"
BUILD_PATH="$2"
SKETCH_PATH="$3"
# Allow BOARDS_TXT as optional 4th parameter, default to original absolute path
BOARDS_TXT="${4:-$HOME/Arduino/hardware/arduino-git/xmc/boards.txt}"

# Extract board name from FQBN (e.g. arduino-git:xmc:kit_xmc47_relax -> kit_xmc47_relax)
BOARD_NAME=$(echo "$FQBN_FULL" | awk -F: '{print $NF}')


# Allow GDB_PATH as optional 5th parameter, default to Infineon toolchain path
GDB_PATH="${5:-$HOME/.arduino15/packages/infineon/tools/arm-none-eabi-gcc/10.3-2021.10/bin/arm-none-eabi-gdb}"

if [[ -z "$FQBN_FULL" || -z "$BUILD_PATH" || -z "$SKETCH_PATH" ]]; then
  echo "Usage: $0 <fqbn> <build_path> <sketch_path> [boards.txt] [gdb_path]"
  exit 1
fi

# 1. Compile
arduino-cli compile -b "${FQBN_FULL}" --build-path "${BUILD_PATH}" "${SKETCH_PATH}" || exit 1

 # 2. Parse boards.txt for variant and board.v using board name
VARIANT=$(grep "^${BOARD_NAME}\.build\.variant=" "$BOARDS_TXT" | cut -d= -f2)
BOARD_V=$(grep "^${BOARD_NAME}\.build\.board\.v=" "$BOARDS_TXT" | cut -d= -f2)

if [[ -z "$VARIANT" || -z "$BOARD_V" ]]; then
  echo "Could not find variant or board.v for $BOARD_NAME in $BOARDS_TXT"

  exit 2
fi

DEVICE="${VARIANT}-${BOARD_V}"
EXECUTABLE=$(find "${BUILD_PATH}" -maxdepth 1 -type f -name "*.elf" | head -n 1)
if [[ -z "$EXECUTABLE" ]]; then
  echo "No .elf executable found in $BUILD_PATH."
  exit 3
fi

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
XMC_DIR="$(dirname "$SCRIPT_DIR")"
LAUNCH_DIR="$XMC_DIR/.vscode"
if [ ! -d "$LAUNCH_DIR" ]; then
  mkdir -p "$LAUNCH_DIR"
fi
if [ -f "$LAUNCH_DIR/launch.json" ]; then
  rm "$LAUNCH_DIR/launch.json"
fi
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

echo "launch.json generated for device ${DEVICE} at $LAUNCH_DIR."
echo "(Using boards.txt at $BOARDS_TXT)"


