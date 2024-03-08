import keywords as k
import re

# Tokens
INT = 'INT'
FLOAT = 'FLOAT'
PLUS = 'PLUS'
MINUS = 'MINUS'
MUL = 'MUL'
DIV = 'DIV'
LPAREN = 'LPAREN'
RPAREN = 'RPAREN'
IDENTIFIER = 'IDENTIFIER'

# Regular expressions for token types
keywords = k.keywordss
identifier = r'abcdefghigklmnopqrstuvwsyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
integer = r'0123456789'
floating = r'0123456789.'
plus = r'+'
minus = r'-'
mul = r'*'
div = r'/'
lparen = r'('
rparen = r')'

# Lexer
def lexer(code):
    tokens = []
    
    remaining = code 
    while len(remaining) > 0:
        match = None

        if re.match(identifier, remaining):
            match = re.match(identifier, remaining)
            tokens.append(IDENTIFIER, match.group(0))
        elif re.match(integer, remaining):
            match = re.match(integer, remaining)
            tokens.append(INT, match.group(0))
        elif re.match(floating, remaining):
            match = re.match(floating, remaining)
            tokens.append(FLOAT, match.group(0))
        elif re.match(plus, remaining):
            match = re.match(plus, remaining)
            tokens.append(PLUS, match.group(0))
        elif re.match(minus, remaining):
             match = re.match(minus, remaining)
             tokens.append(MINUS, match.group(0))
        elif re.match(mul, remaining):
            match = re.match(mul, remaining)
            tokens.append(MUL, match.group(0))
        elif re.match(div, remaining):
            match = re.match(mul, remaining)
            tokens.append(DIV, match.group(0))
        elif re.match(lparen, remaining):
            match = re.match(lparen, remaining)
            tokens.append(LPAREN, match.group(0))
        elif re.match(rparen, remaining):
            match = re.match(rparen, remaining)
            tokens.append(RPAREN, match.group(0))

    return tokens


                
        
