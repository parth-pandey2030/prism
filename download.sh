#!/bin/bash

# Loading Animation Function
spinner() {
    local pid=$1
    local spin='-\|/'
    local i=0
    tput civis 

    while kill -0 $pid 2>/dev/null; do
        local i=$(((i + 1) % ${#spin}))
        printf "\r%s" "Loading ${spin:$i:1}"
        sleep .1
    done

    tput cnorm 
    wait $pid
    return $?
}

# Function to color text
color_text() {
    COLOR=$1
    TEXT=$2

    RESET=${tput sgr0}
    case $COLOR in 
        RED) return "${tput setaf 1} ${TEXT} ${RESET}"
        GREEN) return "${tput setaf 2} ${TEXT} ${RESET}"

}

# Function to figure out which operating system is on the computer.
operating_system() {
    case "$(uname -s)" in
        solaris*) return "SOLARIS" ;;
        darwin*)  return "OSX" ;; 
        linux*)   return "LINUX" ;;
        bsd*)     return "BSD" ;;
        msys*)    return "WINDOWS" ;;
        cygwin*)  return "ALSO WINDOWS" ;;
        *)        return "unknown: $OSTYPE" ;;
    esac
}

# Function to chekc if Python is installed
has_python() {
    python3 --version
    output=$?
    if [ $output -eq 0 ]; then
        return 0
    else
        return 1
    fi
}

# Function to check if PIP is installed (note that pip3 is used)
has_pip() {
    pip3 --version
    output=$?
    if [ $output -eq 0 ]; then
        return 0
    else
        return 1
    fi
}

echo "Downloading sub-modules.... "
has_python
if [ $? -eq 0 ]; then
    echo -e "\e[32mPython is already installed\e[0m"
else
    echo "Installing python..."
    case $(operating_system) in
        SOLARIS)
            pkg install python3
            ;;
        OSX)
            brew install python3
            ;;
        LINUX)
            sudo apt install python3
            ;;
        BSD)
            pkg install python3
            ;;
        WINDOWS)
            choco install python
            ;;
        ALSO_WINDOWS)
            choco install python
            ;;
        *)
            sudo apt install python3
            ;;
    esac
fi

has_pip
if [ $? -eq 0 ]; then
    echo "PIP is already installed"
else
    echo "Installing.... "
    curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
    python3 get-pip.py
    rm get-pip.py
fi 

# Install Python libraries
pip install sympy
pip install Cython
pip install yaml
pip install toml
pip install 

echo "Activating prism.... " 
chmod +x prism/shell/prism
echo "Complete"

echo "Converting prism to shell command.... "
echo "You will need to enter your password:"
sudo mv prism/shell/prism /usr/local/bin
echo "Complete"

echo "You can use Prism now!"