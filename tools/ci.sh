#!/bin/bash

if which nproc > /dev/null; then
    MAKEOPTS="-j$(nproc)"
else
    MAKEOPTS="-j$(sysctl -n hw.ncpu)"
fi

# Ensure known OPEN_MAX (NO_FILES) limit.
ulimit -n 1024

########################################################################################
# commit formatting

function ci_commit_formatting_run {
    git remote add upstream https://github.com/Infineon/XMC-for-Arduino.git
    git fetch --depth=100 upstream master-2.x-3.x
    # If the common ancestor commit hasn't been found, fetch more.
    git merge-base upstream/master-2.x-3.x HEAD || git fetch upstream master-2.x-3.x
    # For a PR, upstream/master-2.x-3.x..HEAD ends with a merge commit, exclude that one.
    python tools/verifygitlog.py --ignore-rebase -v upstream/master-2.x-3.x..HEAD --no-merges
}
