// C++ header file for derivatives
#include "limits/limit.h"

// Function to calculate the limit of a function as it approaches a given value
double derivative(double (*func)(double), double x, double h) {
    return LIMIT(func, x, h);
}

