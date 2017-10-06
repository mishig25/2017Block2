#! /bin/bash

# Compile the serial version
gcc -g -o serial serial.c

# # Compile the OpenMP version
# gcc -o openmp -fopenmp openmp.c
#
# Compile the cilkplus version
g++ -o cilk -fcilkplus cilk.c
