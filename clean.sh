#!/bin/bash

# Find all files in current directory and subdirectories
# that don't have an extension and are executable
find . -type f -executable \
    ! -name "*.sh" \
    ! -name "*.cpp" \
    ! -name "*.h" \
    ! -name "*.md" \
    ! -name "*.txt" \
    ! -name ".*" \
    -delete

echo "Cleaned all executable files"
