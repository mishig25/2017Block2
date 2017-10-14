/**
 * Program to scale and project data into 2D and find a centroid
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <cilk/cilk.h>
#include <map>

/* uses hashmap to improve runtime */
long q(long n, std::map<int, int> *q_vals) {
    if (q_vals->find(n) == q_vals->end()) {
      int val = 1;
      if(!(n<3)){
        // fork
        int x = cilk_spawn q(n - q(n-1,q_vals),q_vals);
        int y = q(n-q(n-2,q_vals),q_vals);
        // join
        cilk_sync;
        val = x + y;
      }
      (*q_vals)[n] = val;
    }
    return q_vals->at(n);
}

int main(int argc, char** argv) {
    long out;
    if(argc!=2) {
        printf("Usage: %s <integer>\nExiting...\n",argv[0]);
        return 1;
    }
    long n = strtol(argv[1],NULL,10);
    std::map<int, int> q_vals; // defining hashmap that will store q vals

    struct timespec start_time;
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC,&start_time);
    out = q(n, &q_vals);
    clock_gettime(CLOCK_MONOTONIC,&end_time);
    long msec = (end_time.tv_sec - start_time.tv_sec)*1000 + (end_time.tv_nsec - start_time.tv_nsec)/1000000;

    // Print output
    printf("q(%d) = %d\n",n,out);
    printf("found in %dms\n",msec);

    return EXIT_SUCCESS;
}
