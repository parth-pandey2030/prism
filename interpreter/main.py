from lexer import *

while True:
    cmd = input('prism >>>>')
    print(Lexer(cmd).tokenize())
