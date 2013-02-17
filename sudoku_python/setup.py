#!/usr/bin/evn python

from distutils.core import setup
from distutils.extension import Extension
 
setup(name="algorithm",
    ext_modules=[
        Extension("algorithm", ["algorithm.cpp"],
        libraries = ["boost_python"])
    ])
