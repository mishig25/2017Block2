#! /bin/bash

# Compile the serial version
gcc -o centroid_serial serial.c 

# Compile the OpenMP version
gcc -o centroid_openmp -fopenmp openmp.c

# Compile the cilkplus version
gcc -o centroid_cilk -fcilkplus cilk.c

# Compile the tbb version
g++ -o centroid_tbb tbb.c -ltbb

# Compile the MPI version
mpicc -o centroid_mpi mpi.c
