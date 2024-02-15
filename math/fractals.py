import numpy as np
import turtle

def mandelbrot():
    points = []
    MAX_ITER = 80
    def f(z, c):
        return (z**2) + c
    

    for z in range(MAX_ITER):
        np