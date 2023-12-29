#!/bin/bash

# Prompt user for concurrency strategy
echo "Choose the concurrency strategy (POOLING or THREADS):"
read -r CONCURRENT_STRATEGY

# Check if the user provided a valid strategy
if [ "$CONCURRENT_STRATEGY" != "POOLING" ] && [ "$CONCURRENT_STRATEGY" != "THREADS" ]; then
    echo "Invalid concurrency strategy. Choose POOLING or THREADS."
    exit 1
fi

# Create a build directory
mkdir -p build
cd build

# Run CMake with the specified concurrency strategy
cmake -DCONCURRENT_STRATEGY="$CONCURRENT_STRATEGY" ..

# Build the project
cmake --build .

# Optionally, you can install the executable or perform additional actions here

echo "Build completed successfully."
