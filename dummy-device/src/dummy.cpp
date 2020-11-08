#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
int main() {
  double next_temp;
  // we want to ensure that we get all of the tests we need.
  // 97.9 - 100.4 degrees Fahrenheit is typical for babies and children.
  // gives an average starting temperature of 99.15.
  srand(time(NULL));
  next_temp =rand()%100;
  
  return 0;
}
