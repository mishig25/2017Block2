#! /bin/sh

# This script runs the serial version of the simulator
# and provides the total runtime.
# 10000 time steps
# radius of 100 units
# 200 particles per emitter
# Emitters at:
#    100, 0
#    -100, 0
#    0, 100
#    0, -100

time ./starhole_serial 10000 100 200 100 0 -100 0 0 100 0 -100

# Execution time of the serial version is roughly 25 seconds on mcscn's
# head node at 6an on 10/5
#Attempting to setup initial state...
#Starting the walks...
#Walks complete... finished with 197376 particles
#Mat out(201, 201, 16)
#
#real    0m25.773s
#user    0m25.756s
#sys 0m0.000s
