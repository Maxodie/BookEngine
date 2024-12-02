# !/bin/bash

# output directory
target="Targets/$1"

# activacte python env
source ~/empty/bin/activacte

# generate cmake build files
cmake -S . -B %target -DCMAKE_BUILD_TYPE=$1 -DCMAKE_TOOLCHAIN_FILE="conanbuildinfo.cmake"

# compile cmake build files
cmake --build $target --config $1
