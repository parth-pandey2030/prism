# Sigma (summation)
class sigma:
    def __init__(self, begin, end, type):
        self.begin = begin
        self.end = end
        self.type = type
        

    # Arithemetic Sum
    def arithemetic_sum_sequence(self, sequence): 
        self.fst = fst = sequence[0]
        self.lst = lst = sequence[-1]
        self.n = n = len(sequence)

        return n/2 * (fst + lst)
    
    def arithemetic_sum_def(self, function, variable):
        self.f = function(variable)
        fst = self.f(self.begin)
        lst = self.f(self.end)

        return self.n/2*(fst+lst)
    
    # Geometric Sum 
    def endless_geometric_sum(self, a, r):
        self.a = a
        self.r = r
        return self.a/(1-self.r)
    
    def geometric_series(a, r, n) :  
        sum = 0
        i = 0
        while i < n :
            sum = sum + a
            a = a * r
            i = i + 1
     
        return sum
     
    def __init__(self, begin, end, type, function = None, variable = None, a = None, r = None, sequence = None):
        self.type = type
        if self.type == 'arithemetic_sum_sequence':
            self.arithemetic_sum_sequence(sequence)

        elif self.type == 'arithemetic_sum_def':
            self.arithemetic_sum_def(function, variable)

        elif self.type == 'endless_geometric_sum':
            self.endless_geometric_sum(a, r)

        elif self.type == 'geometric_series':
            self.geometric_series(a, r, self.end)            
    