#! /bin/bash

# Compile the serial version
gcc -o serial serial.c -lcrypto -lm

# Compile the OpenMP version
gcc -o openmp -fopenmp openmp.c -lcrypto

# Compile the cilkplus version
gcc -o cilk -fcilkplus cilk.c -lcrypto

# Compile the tbb version
g++ -o tbb tbb.c -ltbb

# Compile the MPI version
mpicc -o recover_pins_mpi mpi.c

# recover_pins_
