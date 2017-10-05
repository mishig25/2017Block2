srun g++ -o starhole_serial serial.cpp -lopencv_core -lopencv_imgcodecs  
srun g++ -o starhole_openmp -fopenmp openmp.cpp -lopencv_core -lopencv_imgcodecs 
srun g++ -o starhole_tbb tbb.cpp -ltbb -lopencv_core -lopencv_imgcodecs
srun mpic++ -o starhole_mpi mpi.cpp -lopencv_core -lopencv_imgcodecs
