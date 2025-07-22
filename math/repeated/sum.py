# Sigma (summation)
import ctypes
lib = ctypes.CDLL("../calculus/limits/limit.so").LIMIT
lib.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_float]
lib.restype = ctypes.c_float

import pyximport
pyximport.install()

from calculus.integrals import definite_integral as di
from sympy import symbols

def sum_values(lower_bound: int, upper_bound: int, func):
    """
    This function calculates a sum by adding up each term of the sum.

    Parameters:
        lower_bound (int): the lower bound
        upper_bound (int): the upper bound
        func (func): the function that the sum sums over (e.g., in the sum Σx^2, func(x)=x^2)
    
    Returns:
        int or float: the sum
    """
    sum = 0
    for i in range(lower_bound, upper_bound):
        sum += func(i)

    return sum

def arithemetic_sum_sequence(upper: int):
    """
    This function takes in an upper bound and sums up 
    all the numbers from 1 up to that number.

    Parameters:
        upper (int): the upper bound

    Returns: 
        int: the sum    
    """
    return (upper/2) * (1 + upper)

def geometric_sum(upper_bound: int, a: float, r: float):
    """
    This function takes in an upper bound (that can be infinity)
    and calculates a geometric sum.

    Parameters:
        upper_bound (int of inf): the upper bound
        a (float): the term being multiplied by r
        r (float): the term being raised to the nth power

    Returns:
        float: the sum    
    """
    return a / (1 - r) if upper_bound == float('inf') else a(r ** upper_bound - 1)
    
def limiting_sum(lower_bound: int, upper_bound, func, precision = 0.000000001):
    """
    This function calculates a sum by taking the limit of its partial sums.

    Parameters:
        lower_bound (int): the lower bound
        upper_bound (int or inf): the upper bound (may be infinite)
        func (func): the function that the sum sums over (e.g., in the sum Σx^2, func(x)=x^2)
        precision (int or float): the precision of the limit
    Returns:
        int or float: the sum
    """
    partial_sum = lambda upper: sum_values(lower_bound, upper, func)
    return lib(partial_sum, upper_bound, -precision)

def ramanujan_summation(lower_bound: int, upper_bound, func, precision_for_limit_sum = 0.0000001):
    """
    This function calculates a sum using the Ramanujan summation technique, allowing it to sum many divergent series.
    For example, the sum (using Ramanujan summation) 1+2+3+4+5+6+7+8+9+...=-1/12, and 1+2+4+8+16+32+64+128+256+...=-1.

    Parameters:
        lower_bound (int): the lower bound
        upper_bound (int or inf): the upper bound (may be infinity)
        func (func): the function that the sum sums over (e.g., in the sum Σx^2, func(x)=x^2)
        precision_for_limit_sum (int or float): the precision for the limiting sums involved
    Returns:
        int or float: the sum
    """
    
    C = di(func, symbols('t'), 0, lower_bound) - 0.5 * func(0)
