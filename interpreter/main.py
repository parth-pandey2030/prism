from lexer import *

while True:
    cmd = input('prism >>>>')
    print(lexer(cmd).tokenize())
