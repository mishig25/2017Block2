#! /bin/bash

# Compile the serial version
gcc -o serial serial.c

# Compile the OpenMP version
gcc -o reduce_openmp -fopenmp openmp.c

# Compile the cilkplus version
gcc -o reduce_cilk -fcilkplus cilk.c
