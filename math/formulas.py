from prism.constants import *
from prism.sum import sigma
from sympy import Symbol 

# Reimann Zeta Function
def zeta(s):
    def f(n):
        return 1/(n**s)
    
    n = Symbol('n')
    return sigma(1, infinity, 'endless_geometric_sum', f, n)

# E = mc^2
def E(m):
    return m*c^2

