#!/bin/bash

# Module installation
sudo apt install python3-pip
pip install sympy
pip install cython
pip install setuptools
pip install julia
pip install yaml
pip install toml

# Command Setup
chmod +x prism
sudo mv prism /usr/local/bin

