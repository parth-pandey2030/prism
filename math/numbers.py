# This file contains numbers important for mathematics (e.g., the Bernoullli numbers).

import pyximport
pyximport.install()

from calculus.integrals import definite_integral as di
from math import pi, exp, inf
from sympy import symbols

def Bernoulli(n):
    """
    The nth Bernoulli number, where n is the argument ot the function. 
    The nth Bernoulli number is calculated through the formula: B_2n=4n(-1)^(n+1) * ∫_0^∞(t^(2n-1) / (exp(2πt)-1)dt)
    """
    t = symbols('t')
    n /= 2
    alg_factor = 4 * n * (-1) ** (n + 1) # This is the term 4n(-1)^(n+1), and is algebraic.
    calc_factor = di(t ** (2n - 1) / exp(2 * pi * t) -1, t, 0, inf)
    return alg_factor * calc_factor