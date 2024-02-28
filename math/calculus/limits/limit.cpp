#include <iostream>
#include <cmath>

// Function to calculate the limit of a function as it approaches a given value
double limit(double (*func)(double), double a, double h) {
    return func(a + h);
}
