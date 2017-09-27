#include "stdio.h"

int fib(int n){
  if(n == 1) return 0;
  else if(n == 2) return 1;
  else return fib(n-1)+fib(n-2);
}

int main(int argc, char** argv){
  int i = 1;
  while(i<=5){
    int fib_number = fib(i);
    printf("%dth Fib Number: %d\n",i,fib_number);
    ++i;
  }
  return 0;
}
