The program computes a value in the Q-Sequence
http://mathworld.wolfram.com/HofstadtersQ-Sequence.html

#############################################################
# Build instructions

To build/run on mcscn you will need to load:
gcc-7.2.0
tbb-2018
slurm

To run the compilation use the compile script:
./compile.sh


#############################################################
# Running the program

The program includes static code to initialize the objects, so no arguments are needed to start the program.

To run the serial version:
./serial 40

To run the OpenMP version:
./openmp 40

To run the cilk version:
./cilk 40
