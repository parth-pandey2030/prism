# Pi (multiplication)
def Pi(begin, end, func):
    result = 1
    i = begin
    while i < end + 1:
        result *= i
        i += 1
    
    return result