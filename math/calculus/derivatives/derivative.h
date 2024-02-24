#include <stdio.h>
#include <math.h>

// Function whose derivative we want to calculate
double function(double x) {
    return x * x; // Example function: f(x) = x^2
}

// Function to calculate the derivative using finite difference method
double derivative(double x, double h) {
    return (function(x + h) - function(x)) / h;
}

int main() {
    double x = 2.0; // Point at which we want to calculate the derivative
    double h = 0.0001; // Step size for finite difference method

    // Calculate and print the derivative
    printf("The derivative of f(x) = x^2 at x = %.2f is approximately: %.6f\n", x, derivative(x, h));

    return 0;
}