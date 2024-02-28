cdef extern from "limit.cpp":
    double limit(double (*func)(double), double a, double h)

    