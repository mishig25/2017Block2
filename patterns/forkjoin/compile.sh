#! /bin/bash

# Compile the serial version
g++ -g -o serial serial.cpp

# Compile the OpenMP version
g++ -o openmp -fopenmp openmp.cpp

# Compile the cilkplus version
g++ -o cilk -fcilkplus cilk.cpp
