#! /bin/sh

# This script runs the serial version of the simulator several times and
# names the output file so that they can be used like a flip book
# 10000 time steps
# radius of 100 units
# 200 particles per emitter
# Emitters at:
#    100, 0
#    -100, 0
#    0, 100
#    0, -100

./starhole_serial 100 100 200 100 0 -100 0 0 100 0 -100
cp out.jpg out_1.jpg
./starhole_serial 200 100 200 100 0 -100 0 0 100 0 -100
cp out.jpg out_2.jpg
./starhole_serial 300 100 200 100 0 -100 0 0 100 0 -100
cp out.jpg out_3.jpg
./starhole_serial 400 100 200 100 0 -100 0 0 100 0 -100
cp out.jpg out_4.jpg
./starhole_serial 500 100 200 100 0 -100 0 0 100 0 -100
cp out.jpg out_5.jpg
./starhole_serial 600 100 200 100 0 -100 0 0 100 0 -100
cp out.jpg out_6.jpg
./starhole_serial 700 100 200 100 0 -100 0 0 100 0 -100
cp out.jpg out_7.jpg
./starhole_serial 800 100 200 100 0 -100 0 0 100 0 -100
cp out.jpg out_8.jpg
./starhole_serial 900 100 200 100 0 -100 0 0 100 0 -100
cp out.jpg out_9.jpg
./starhole_serial 1000 100 200 100 0 -100 0 0 100 0 -100
cp out.jpg out_10.jpg
./starhole_serial 1100 100 200 100 0 -100 0 0 100 0 -100
cp out.jpg out_11.jpg
./starhole_serial 1200 100 200 100 0 -100 0 0 100 0 -100
cp out.jpg out_12.jpg
