from sympy import Symbol
import ctypes
import math
lib = ctypes.CDLL('./math/calculus/limit.so')
def f(x):
    return math.sin(x)/x

lib.limit(f, 0.0, 0.0000001)
class derivative:
    def __init__(self, function, variable):
        self.variable = Symbol(variable)
        self.function = function
        self.main()

    def main(self):
        pass

