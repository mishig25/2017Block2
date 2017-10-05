#! /bin/bash

# Due to the GCC incompatibility, all compilation needs to be done on 
# compute nodes... super lame... sorry.

# Compile the serial version.
srun bash compile2.sh
