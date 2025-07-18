// C++ header file for derivatives
#include "limits/limit.h"

// Function to calculate the limit of a function as it approaches a given value
template <typename T>
T derivative(T (*func)(T), T x, T h) {
    return LIMIT((func(x + h) - func(x)) / h, x, h);
}

