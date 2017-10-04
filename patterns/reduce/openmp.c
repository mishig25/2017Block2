/**
 * Program to scale and project data into 2D and find a centroid
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define N 80842401
float x[N];
float y[N];
float z[N];
float mass[N];
// int list[N];

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
  // float* x[80842401];
  // float* y[80842401];
  // float* z[80842401];
  // float* mass[80842401];
};

// Add phaseball to a volume
void volume_append(struct volume* v, struct phaseball* o, int ctr) {
    if( v->last == v->size ) {
        (v->size) += 100;
        v->objects = realloc(v->objects, sizeof(struct phaseball*)*(v->size)+100);
    }
    (v->objects)[(v->last)] = o;
    (v->last) += 1;

    x[ctr] = o->x;
    y[ctr] = o->y;
    z[ctr] = o->z;
    mass[ctr] = o->mass;

    return;
}

// Place phaseballs uniformly in a box, with mass equal to the manhattan distance
void place_uniformly(int sx, int ex, int sy, int ey, int sz, int ez, struct volume* v) {
  int counter = 0;
    for(int i=sx; i<=ex; i++) {
        for(int j=sy; j<=ey; j++) {
            for(int k=sz; k<=ez; k++) {
                struct phaseball* n = malloc(sizeof(struct phaseball));
                n->x = i;
                n->y = j;
                n->z = k;
                n->mass = 1;
                n->mass = fabs(n->x)+fabs(n->y)+fabs(n->z);
                volume_append(v,n,counter);
                counter ++;
            }
        }
    }
    printf("Count: %d\n",counter);
}

// Projects 3D volume to 11x11 2D map and report centroid
void post_process(struct volume* v, float* cx, float* cy) {
    double mass_sum=0.0;
    double wx=0.0;
    double wy=0.0;

    #pragma omp parallel for reduction(+:mass_sum,wx,wy)
    for(int i=0; i<v->last; i++){
      // struct phaseball* o = v->objects[i];
      mass_sum += mass[i];
      wx += x[i] * mass[i];
      wy += y[i] * mass[i];
    }

    *cx = wx/mass_sum;
    *cy = wy/mass_sum;

    return;
}

int main(int argc, char** argv) {
    int *list;
    list  = (int *) malloc(N * sizeof(int));
    // make a volume to store objects in
    struct volume v;
    v.size=100;
    v.last=0;
    v.objects = malloc(sizeof(struct phaseball*)*100);

    // struct of arrays
    struct SoA soa;

    // Set the initial configuration
    place_uniformly(-1000,1000,-100,100,-100,100,&v);

    // Generate output
    float cx,cy;
    struct timespec start_time;
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC,&start_time);
    post_process(&v, &cx, &cy);
    clock_gettime(CLOCK_MONOTONIC,&end_time);
    long msec = (end_time.tv_sec - start_time.tv_sec)*1000 + (end_time.tv_nsec - start_time.tv_nsec)/1000000;

    // Print output
    printf("Centroid at: %f,%f\n",cx,cy);
    printf("found in %dms\n",msec);

    int n = sizeof(list)/sizeof(int);
    printf("Length in %d\n",v.last);
    return EXIT_SUCCESS;
}
