class Limit:
    def __init__(self, function, variable, value):
        self.function = function
        self.variable = variable 
        self.value = value
        self.main()

    def main(self):
        from derivatives import derivative as deri
        try:
            pass

        except:
            function = deri(self.function, self.variable).main()
            return function(self.value)