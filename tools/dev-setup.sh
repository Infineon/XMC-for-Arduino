#!/bin/bash

# Change dir to the directory where this script is located
cd $(dirname $0)
echo ${PWD}

function git_submodule_setup {
    git submodule update --init --recursive
}

function core_api_setup {

    cores_xmc_dir="${PWD}/../cores/xmc"
    core_api_submodule_dir="${PWD}/../extras/arduino-core-api"

    # Create symbolic link (overwrite) to the api/ 
    # folder of ArduinoCore-API submodule.
    # Note: Symlinks might not work without full paths
    # https://stackoverflow.com/questions/8601988/symlinks-not-working-when-link-is-made-in-another-directory
    if [ ! -d "$cores_xmc_dir" ]; then
        mkdir -p "$cores_xmc_dir"
        echo "Directory created: $cores_xmc_dir"
    fi
    ln -sf ${core_api_submodule_dir}/api ${cores_xmc_dir}
}


# Check if a function name is passed as an argument
if [ $# -gt 0 ]; then
    if declare -f "$1" > /dev/null; then
        "$1"
    else
        echo "Function $1 not found"
        exit 1
    fi
else
    git_submodule_setup
    # core_api_setup disable for XMC4Arduino 3.x 
fi
