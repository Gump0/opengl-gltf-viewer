#!/usr/bin/env bash
set -e

BUILD_DIR="build"
EXECUTABLE_NAME="gltf-viewer"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"
rm -rf build # ensure that build folder is cleaned before rebuilding

cmake -B "$BUILD_DIR"
cmake --build "$BUILD_DIR" --target run # forces to launch program from build folder

echo "Running $EXECUTABLE_NAME.."
