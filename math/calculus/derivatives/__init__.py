from sympy.abc import x
class derivative:
    def __init__(self, function, variable = x):
        self.function = function
        self.variable = variable
        self.main()

    def main(self):
        if type(function) == int:
            return 0
        else:
            pass