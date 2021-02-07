#!/bin/bash

## Config
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)/.."
BUILD_DIR="$ROOT_DIR/build"
BIN_DIR="$ROOT_DIR/bin"
RESOURCE_DIR="$ROOT_DIR/resources"
SHADERS_DIR="$ROOT_DIR/src/engine/shader"
EXECUTABLE=QNAGE

CMAKE=cmake
MAKE=make
MAKE_PARAMS="-j4"
##

# Preparation stage
mkdir -p "$BUILD_DIR"
mkdir -p "$BIN_DIR"

# Build stage
cd "$BUILD_DIR"
$CMAKE "$ROOT_DIR"
$MAKE "$MAKE_PARAMS"

# Final stage
cp "$BUILD_DIR/$EXECUTABLE" "$BIN_DIR/$EXECUTABLE"
cp -R "$RESOURCE_DIR" "$BIN_DIR"
cp -R "$SHADERS_DIR" "$BIN_DIR"

echo "Done, executable path: $BIN_DIR"
