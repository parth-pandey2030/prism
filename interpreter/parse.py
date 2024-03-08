from lexer import lexer

file = None
contents = open(file, "r").read()

# Use Lexer
lex = lexer(contents)

def parser(code):
    pass

