from sympy import symbols, integrate

C = constant_of_integration = symbols('C')
def antiderivative(function):
    return integrate(function) + C

def definite_integral(function, var, a, b):
    return integrate(function, (var, a, b))

def line_integral(curve_endpoint_1, curve_endpoint_2, function):
    return function(curve_endpoint_2) - function(curve_endpoint_1)