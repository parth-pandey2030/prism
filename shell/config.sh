#!/bin/bash

# Module installation
sudo apt install python3-pip
pip install sympy
pip install cython
pip install setuptools
pip install julia

# Module installation using pip3 (command "pip" may need some variation)
pip3 install sympy
pip3 install cython
pip3 install setuptools
pip3 install julia

# Command Setup
chmod +x prism
sudo mv prism /usr/local/bin

