#!/bin/bash

echo "Building the project..."
make

if [ $? -ne 0 ]; then
    echo "Build failed. Exiting."
    exit 1
fi

echo "🚗 Running simulation..."
./build/a.out

if [ $? -ne 0 ]; then
    echo "Simulation crashed. Exiting."
    exit 1
fi

echo "Plotting results..."
python3 script/plot.py

echo "Finished."
