#!/bin/bash

# Designed to easily compile C/C++ scripts.
echo "C/C++ script location: "
read $location

echo "Output file name: "
read $name

g++ -shared -o $name -fPIC $location


