/**
 * This program takes in a hash and attempts to find a matching 8 digit pin
 */

// sprintf, printf
#include <stdio.h>

// strlen, strncmp
#include <string.h>

// exit value
#include <stdlib.h>

// md5 hash function
#include <openssl/md5.h>

// clock measurements
#include <time.h>

// openmp for parallelism
#include <omp.h>

// math utilities
#include <math.h>

// valid pin characters
const char* chars="0123456789";

// tests if a hash matches a candidate password
int test(const char* passhash, const char* passcandidate) {
    unsigned char digest[MD5_DIGEST_LENGTH]; // hash storage

    // Compute the hash
    MD5((unsigned char*)passcandidate, strlen(passcandidate), digest);

    // Convert the hash to a base 16 string
    char mdString[34];
    mdString[33]='\0';
    for(int i=0; i<16; i++) {
        sprintf(&mdString[i*2], "%02x", (unsigned char)digest[i]);
    }

    // return the value of the comparison
    return strncmp(passhash, mdString, strlen(passhash));
}

// maps a numeric PIN to a string
void genpass(long passnum, char* passbuff) {
    passbuff[8]='\0'; // enforce null termination
    int charidx; // character within array of valid characters

    // determine the "base" for the pin string
    int symcount=strlen(chars);

    // perform the conversion
    for(int i=7; i>=0; i--) {
        charidx=passnum%symcount;
        passnum=passnum/symcount;
        passbuff[i]=chars[charidx];
    }
}

// run parallel process for checking pins
void start_parallel_check(char* given_key){
  char passmatch[9]; // buffer for the matched password

  // variables for the timer
  struct timespec start_time;
  struct timespec end_time;
  long msec;

  clock_gettime(CLOCK_MONOTONIC,&start_time);

  long max_comb = pow(10,8);
  int notfound=1;
  int answer;
  int can_proceed = 1;
  omp_lock_t lockA;
  omp_init_lock(&lockA);

  #pragma omp parallel for
  for(int i=0; i<max_comb; i++){
    if(can_proceed == 1){
      // prevents from starting other parallel processes once answer is found
      // this process is achieveing at least 2X speedup
      genpass(i,passmatch);
      notfound=test(given_key, passmatch);
      if(!notfound){
        // set can_proceed and answer
        omp_set_lock(&lockA);
        can_proceed = 0;
        answer = i;
        omp_unset_lock(&lockA);
      }
    }
  }
  clock_gettime(CLOCK_MONOTONIC,&end_time);

  // convert the time to elapsed milliseconds
  msec = (end_time.tv_sec - start_time.tv_sec)*1000 + (end_time.tv_nsec - start_time.tv_nsec)/1000000;

  // handling non-determinism caused by parallelism
  if(can_proceed == 1){
    printf("Answer did not come out. Running the process again ...\n");
    start_parallel_check(given_key);
  }else{
    printf("found: %8d in %dms\n",answer,msec);
  }
}

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("Usage: %s <password hash>\n",argv[0]);
        return 1;
    }
    
    start_parallel_check(argv[1]);

    return EXIT_SUCCESS;
}
