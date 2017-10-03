#! /bin/bash

# Compile the serial version
gcc -o serial serial.c -lcrypto -lm

# Compile the OpenMP version
gcc -o recover_pins_openmp -fopenmp openmp.c -lcrypto

# Compile the cilkplus version
gcc -o recover_pins_cilk -fcilkplus cilk.c -lcrypto
