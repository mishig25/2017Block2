srun g++ -o stencil_serial serial.cpp -lopencv_core -lopencv_imgcodecs  
srun g++ -o stencil_openmp -fopenmp openmp.cpp -lopencv_core -lopencv_imgcodecs 
srun g++ -o stencil_tbb tbb.cpp -ltbb -lopencv_core -lopencv_imgcodecs
srun mpic++ -o stencil_mpi mpi.cpp -lopencv_core -lopencv_imgcodecs
