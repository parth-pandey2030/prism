# Sigma (summation)
def arithemetic_sum_sequence(upper: int):
    """
    This function takes in an upper bound and sums up 
    all the numbers from 1 to that number.

    Parameters:
        int: the upper bound

    Returns: 
        int: the sum    
    """
    return (upper/2) * (1 + upper)

print(arithemetic_sum_sequence(10))