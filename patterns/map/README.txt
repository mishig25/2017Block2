The recover_pins program takes in a md5 hashed numeric pin and outputs
a corrasponding plaintext pin.


#############################################################
# Build instructions

To build/run on mcscn you will need to load:
gcc-7.2.0
openssl-1.1.0
tbb-2018
slurm
openmpi-3.3.0

To run the compilation use the compile script:
./compile.sh


#############################################################
# Running the program

To create a hashed pin for pin 00000000:
echo -n "00000000" | md5sum

To recover a pin using the serial version:
./recover_pins_serial dd4b21e9ef71e1291183a46b913ae6f2

To recover a pin using the OpenMP version:
./recover_pins_openmp dd4b21e9ef71e1291183a46b913ae6f2

To recover a pin using the cilkplus version:
./recover_pins_cilk dd4b21e9ef71e1291183a46b913ae6f2

To recover a pin using the tbb version:
./recover_pins_tbb dd4b21e9ef71e1291183a46b913ae6f2

To recover a pin using the MPI version:
srun -N1 -n32 ./recover_pins_mpi dd4b21e9ef71e1291183a46b913ae6f2


