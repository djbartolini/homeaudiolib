#!/bin/bash

# Set output executable name
OUTPUT="homeaudio"

# Find all CPP files in current directory and subdirectories
CPP_FILES=$(find . -name "*.cpp" -not -path "./cmake-build-debug/*")

# Check if any .cpp files are found
if [ -z "$CPP_FILES" ]; then
  echo "No .cpp files found"
  exit 1
fi

# Compile all .cpp files into output executable
clang++ -std=c++17 -o $OUTPUT $CPP_FILES -framework AudioToolbox

# Check if compile was successful
if [ $? -eq 0 ]; then
  echo "Compilation successful. Executable created: $OUTPUT"
else
  echo "Compilation failed."
  exit 1
fi