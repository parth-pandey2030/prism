# Pi (multiplication)
import ctypes

lib = ctypes.CDLL("../calculus/limits/limit.so").LIMIT
lib.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_float]
lib.restype = ctypes.c_float

def finite_multiplication(begin, end, func):
    result = 1
    i = begin
    while i < end + 1:
        result *= i
        i += 1
    
    return result

def infinite_multiplication(begin, func):
    pass # Define Infinite Multiplication 