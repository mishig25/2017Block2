#! /bin/bash

# Compile the serial version
gcc -o serial serial.c -lcrypto -lm

# Compile the OpenMP version
gcc -o openmp -fopenmp openmp.c -lcrypto

# Compile the cilkplus version
gcc -o cilk -fcilkplus cilk.c -lcrypto

# recover_pins_
