#!/usr/bin/env bash

BRIGHT_RED="\e[31;1m"
BRIGHT_GREEN="\e[32;1m"
RESET="\e[0m"

function error {
    echo -e "${BRIGHT_RED}Build error${RESET}"
    exit 1
}

mkdir -p build/
cd build/
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug .. || error
ninja || error

echo -e "${BRIGHT_GREEN}Build success${RESET}"
echo "Running..."
echo "-------- PROGRAM START ---------"
./zydeco
EC=$?
echo "--------- PROGRAM END ----------"
echo "Exited with $EC"
