/**
 * Program to scale and project data into 2D and find a centroid
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

/* struct to hold objects attributes */
struct phaseball {
    float x;
    float y;
    float z;
    float mass;
};

struct volume {
    size_t size;
    size_t last;
    struct phaseball** objects;
};

// structure of arrays
struct SoA{
  float* x;
  float* y;
  float* z;
  float* mass;
};

// Add phaseball to a volume
void volume_append(struct volume* v, struct phaseball* o, int ctr) {
    if( v->last == v->size ) {
        (v->size) += 100;
        v->objects = realloc(v->objects, sizeof(struct phaseball*)*(v->size)+100);
    }
    (v->objects)[(v->last)] = o;
    (v->last) += 1;
    return;
}

// Place phaseballs uniformly in a box, with mass equal to the manhattan distance
int place_uniformly(int sx, int ex, int sy, int ey, int sz, int ez, struct SoA* soa){
  int counter = 0;
  int number_of_phaseballs = (ex-sx+1)*(ey-sy+1)*(ez-sy+1);
  soa->x = (float *) malloc(number_of_phaseballs * sizeof(float));
  soa->y = (float *) malloc(number_of_phaseballs * sizeof(float));
  soa->z = (float *) malloc(number_of_phaseballs * sizeof(float));
  soa->mass = (float *) malloc(number_of_phaseballs * sizeof(float));
  for(int i=sx; i<=ex; i++) {
        for(int j=sy; j<=ey; j++) {
            for(int k=sz; k<=ez; k++) {
                soa->x[counter] = i;
                soa->y[counter] = j;
                soa->z[counter] = k;
                soa->mass[counter] = fabs(i)+fabs(j)+fabs(k);
                counter ++;
            }
        }
    }
  return number_of_phaseballs;
}

void post_process(struct SoA* soa, float* cx, float* cy, int length) {
    double mass_sum=0.0;
    double wx=0.0;
    double wy=0.0;

    #pragma omp parallel for reduction(+:mass_sum,wx,wy)
    for(int i=0; i<length; i++){
      // struct phaseball* o = v->objects[i];
      mass_sum += soa->mass[i];
      wx += soa->x[i] * soa->mass[i];
      wy += soa->y[i] * soa->mass[i];
    }

    *cx = wx/mass_sum;
    *cy = wy/mass_sum;

    return;
}

int main(int argc, char** argv) {
    // make a volume to store objects in
    struct volume v;
    v.size=100;
    v.last=0;
    v.objects = malloc(sizeof(struct phaseball*)*100);

    // struct of arrays
    struct SoA soa;
    // Set the initial configuration
    // place_uniformly(-1000,1000,-100,100,-100,100,&v,&soa);

    int length_of_arr = place_uniformly(-1000,1000,-100,100,-100,100,&soa);
    // Generate output
    float cx,cy;
    struct timespec start_time;
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC,&start_time);
    post_process(&soa, &cx, &cy, length_of_arr);
    clock_gettime(CLOCK_MONOTONIC,&end_time);
    long msec = (end_time.tv_sec - start_time.tv_sec)*1000 + (end_time.tv_nsec - start_time.tv_nsec)/1000000;

    // Print output
    printf("Centroid at: %f,%f\n",cx,cy);
    printf("found in %dms\n",msec);

    return EXIT_SUCCESS;
}
