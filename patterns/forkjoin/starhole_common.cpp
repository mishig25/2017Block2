#ifndef STARHOLE_HELPERS
#define STARHOLE_HELPERS

// Represents the probability that a Carter particle will move to a nearby cell
// The structure is read as r < prob[i]; prob[i] is a summation of the probabilities
// of the cells checked earlier with the probability of the current cell
typedef struct _dirUpdate {
    double prob[9];
} DirUpdate;

// Helper function for writing out DirUpdate data
void dumpProb(double probdat[9]) {
    printf("%f\t%f\t%f\n",probdat[0],probdat[1],probdat[2]);
    printf("%f\t%f\t%f\n",probdat[3],probdat[4],probdat[5]);
    printf("%f\t%f\t%f\n",probdat[6],probdat[7],probdat[8]);
}


// distance from origin
double dist(int x, int y) {
    return sqrt(x*x + y*y);
}

// Maps between a coordinate plane with origin 0,0 and the linear array
int toOffset(int x, int y, int radius) {
    x = x + radius;
    y = y + radius;
    return x + (y * (2 * radius + 1));
}

// Gaussian distributions are nice
double gaussianFunc(double x, double x0, double a, double dev) {
    return a*exp(-(x-x0)*(x-x0)/(2*dev*dev));
}

// Split probabilities
double computeSplitProb(int x, int y, int radius) {
    return 0.001*(dist(x,y)/radius);
}

// Packs a DirUpdate struct for coordinates x,y on a plane of radius radius
void computeDirProb(int x, int y, int radius, DirUpdate* loc) {
    loc->prob[0] = dist(x-1,y+1);
    loc->prob[1] = dist(x,y+1);
    loc->prob[2] = dist(x+1,y+1);
    loc->prob[3] = dist(x-1,y);
    loc->prob[4] = dist(x,y);
    loc->prob[5] = dist(x+1,y);
    loc->prob[6] = dist(x-1,y-1);
    loc->prob[7] = dist(x,y-1);
    loc->prob[8] = dist(x+1,y-1);
    double acc = 0.0;
    for(int i=0;i<9;i++) {
        if(loc->prob[i] < radius) { 
            loc->prob[i] = 2*gaussianFunc(loc->prob[i],0,1,sqrt(radius)) + gaussianFunc(loc->prob[i],radius/2,1,sqrt(radius*4))+.01;
            acc+=loc->prob[i]; loc->prob[i] = acc; 
        } else { loc->prob[i] = 0.0; }
    }
    for(int i=0;i<9;i++) {
        loc->prob[i] = loc->prob[i]/acc;
    }
}

// Helper function to determine if a split occurs
int doesSplit(struct drand48_data* seedbuf, double* splitProb, int x, int y, int radius) {
    double r;
    drand48_r(seedbuf,&r);
    if(r < splitProb[toOffset(x,y,radius)]) {
        return 1;
    }
    return 0;
}

// Helper function to update a particle location
void updateLocation(struct drand48_data* seedbuf, DirUpdate* area, int* x, int *y, int radius) {
    double r;
    drand48_r(seedbuf,&r);
    DirUpdate d = area[toOffset(*x, *y, radius)];
    if(r<d.prob[0]) { *x = *x - 1; *y = *y + 1; } // ul
    else if(r<d.prob[1]) {              *y = *y + 1; } // u
    else if(r<d.prob[2]) { *x = *x + 1; *y = *y + 1; } // ur
    else if(r<d.prob[3]) { *x = *x - 1;              } // l
    else if(r<d.prob[4]) {                           } // 
    else if(r<d.prob[5]) { *x = *x + 1;              } // r
    else if(r<d.prob[6]) { *x = *x - 1; *y = *y - 1; } // ll
    else if(r<d.prob[7]) {              *y = *y - 1; } // l
    //if(d.prob[8]<r) { *x = *x + 1; *y = *y - 1; return; }
    // otherwise, lower right
    else { *x = *x + 1; *y = *y - 1; }
    
    return;
}

// Helper to initialize needed data structures
void initialize(int radius, int**oa, double** sp, DirUpdate** a) {
    int rows = 2*radius+1;
    int cols = 2*radius+1;
    
    int* outArea = (*oa) = (int*)calloc(rows*cols,sizeof(int));
    double* splitProb = (*sp) = (double*)malloc(sizeof(double)*rows*cols);
    DirUpdate* area = (*a) = (DirUpdate*)malloc(sizeof(DirUpdate)*rows*cols);
    
    for(int i=-radius;i<radius+1;i++) {
        for(int j=-radius;j<radius+1;j++) {
            int offset = toOffset(i,j,radius);
            // pack split prob -- i,j
            splitProb[offset] = computeSplitProb(i,j,radius);
            // pack dir update -- i,j
            computeDirProb(i,j,radius,&(area[offset]));
        }
    }
}

int readArgs(int argc, char** argv, int* sim_steps, int* radius, int* amount, int* coordPairs, int** coords) {
    char* endptr;
    endptr = argv[1];
    *sim_steps = (unsigned)strtol(argv[1],&endptr,10);
    if(*endptr != 0 || *sim_steps < 0) {
        printf("Steps must be a positive integer\n");
        return 1;
    }
    endptr=argv[2];
    *radius = (unsigned int)strtol(argv[2],&endptr,10);
    if(*endptr != 0 || *radius>5000 || *radius < 1) {
        printf("Radius must be a positive integer less than 5000\n");
        return 1;
    }
    
    endptr = argv[3];
    *amount = (int)strtol(argv[3],&endptr,10);
    if(*endptr != 0 || *amount>10000 || *amount < 1) {
        printf("Amount must be a positive integer less than 10000\n");
        return 1;
    }

    *coordPairs = (argc-4)/2;    
    (*coords)=(int*)malloc(sizeof(int)*(*coordPairs)*2);
    for(int i=0; i<argc-4; i+=2) {
        endptr = argv[i+4];
        (*coords)[i] = (int)strtol(argv[i+4],&endptr,10);
        if(*endptr != 0 ) {
            printf("Coordinate must fit in radius.");
            return 1;
        }
        endptr = argv[i+5];
        (*coords)[i+1] = (int)strtol(argv[i+5],&endptr,10);
        if(*endptr != 0 || dist((*coords)[i],(*coords)[i+1])>*radius) {
            printf("Coordinate must fit in radius.");
            return 1;
        }
    }
    return 0;
}

void writeOutput(int radius, int* outArea) {
    // Generate the output
    int rows = radius*2+1;
    int cols = radius*2+1;
 
    // find the cell with the most
    int max=0;
    for(int i=0;i<rows*cols; i++) {
        if(outArea[i]>max) {
            max=outArea[i];
        }
    }
    // Generate the output image
    printf("Mat out(%d, %d, %d)\n",radius*2+1, radius*2+1,CV_8UC3);
    Mat out(rows, cols, CV_8UC3);
    for(int i=0;i<radius*2+1;i++) {
        for(int j=0;j<radius*2+1;j++) {
            const size_t offset = i + (j*(radius*2+1));
            // paint the ring
            double ring=0.0;
            if(dist(i-radius,j-radius)<=radius) {
               ring = 1.0;
            }
            double intensity = sqrt((double)outArea[offset]/(double)max);

            if(intensity>0) {
            out.at<Vec3b>(i, j) = Vec3b(floor(intensity * 255.0),
                                        floor(intensity * 255.0),
                                        floor(intensity * 255.0));
            } else {
            out.at<Vec3b>(i, j) = Vec3b(floor(0 * 255.0),
                                        floor(0 * 255.0),
                                        floor(ring * 128.0));
            }
        }
    }
    imwrite("out.jpg", out);
}
#endif
