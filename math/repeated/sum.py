# Sigma (summation)
def arithemetic_sum_sequence(upper: int):
    """
    This function takes in an upper bound and sums up 
    all the numbers from 1 to that number.

    Parameters:
        upper (int): the upper bound

    Returns: 
        int: the sum    
    """
    return (upper/2) * (1 + upper)

def geometric_sum(upper_bound: int, a: float, r: float):
    """
    This function takes in an upper bound (that can be infinity)
    and does a geometric sum.

    Parameters:
        upper_bound (int of inf): the upper bound
        a (float): the term being multiplied by r
        r (float): the term being raised to the nth power

    Returns:
        float: the sum    
    """
    return a / (1 - r) if upper_bound == float('inf') else a(r ** upper_bound - 1)
    
def ramanujan_summation()