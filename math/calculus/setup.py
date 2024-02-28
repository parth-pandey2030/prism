from setuptools import setup
from setuptools.extension import Extension
from Cython.Build import cythonize

setup(
    ext_modules = cythonize([
        Extension(
            name="limit",
            sources=["math/calculus/limit.pyx", "math/calculus/limits/limit.cpp"],
            language="c++"
        )
    ])
)