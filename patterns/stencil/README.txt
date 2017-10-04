Since there are a few projects that are working with images, an example using the stencil pattern and an image library seemed like it would be useful. The code I had to work from is C++, but is written in a mostly C style.

Completing the lab involves figuruing out what loop(s) to make parallel in apply_stencil to improve performance for large images and figuring out how to apply the prewitt kernels for edge detection. Please do this for two of the four parallel technologies available in this course.

Note: OpenCV is being used to access the image data. The OpenCV headers expose the same GCC defect on mscn that the TBB headers expose. To get around this, compilation should be done on the compute nodes. The compile.sh script starts a job on the compute nodes (compile2.sh) that actually completes the compilation. The resulting binaries will run on the headnode.

A small image to try blurring and edge detection with is hosted at:
http://cs.coloradocollege.edu/~dellsworth/cat.jpg

A much larger image from NASA is at:
http://cs.coloradocollege.edu/~dellsworth/image.jpg

You can use wget or curl to download these images.


The following modules should be loaded before working with this code:
slurm
gcc-7.2.0
opencv-3.3.0
tbb-2018
openmpi-3.0.0
