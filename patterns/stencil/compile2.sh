srun g++ -o stencil_serial serial.cpp -lopencv_core -lopencv_imgcodecs
srun g++ -o stencil_openmp -fopenmp openmp.cpp -lopencv_core -lopencv_imgcodecs
srun g++ -o stencil_cilk -fcilkplus cilk.cpp -lopencv_core -lopencv_imgcodecs
