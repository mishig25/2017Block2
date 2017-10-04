The centroid program initializes a number of objects in 3D space with masses equal to the manhatten distance from the origin, then computes the centroid (weighted average) in the x,y plane.

#############################################################
# Build instructions

To build/run on mcscn you will need to load:
gcc-7.2.0
tbb-2018
slurm
openmpi-3.3.0

To run the compilation use the compile script:
./compile.sh


#############################################################
# Running the program

The program includes static code to initialize the objects, so no arguments are needed to start the program.

To run the serial version:
./centroid_serial

To run the OpenMP version:
./centroid_openmp

To run the cilk version:
./centroid_cilk
