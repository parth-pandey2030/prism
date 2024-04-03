from sympy import symbols, integrate
from sympy.abc import X
C = constant_of_integration = symbols('C')
cdef antiderivative(function):
    return integrate(function) + C

cdef definite_integral(function, var, a, b):
    return integrate(function, (var, a, b))

cdef line_integral(curve_endpoint_1, curve_endpoint_2, function):
    return function(curve_endpoint_2) - function(curve_endpoint_1)\
    



    