#!/bin/bash

echo "Activating prism.... "
chmod +x prism/shell/prism
echo "Complete"

echo "Converting prism to shell command.... "
sudo mv prism/shell/prism /usr/local/bin
echo "Complete"
