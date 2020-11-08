#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
bool get_command(next_temp) {  
  <<next_temp;
  >>temp_status;
  
  return temp_status;    
}

double send_temperature(bool temp_status) {
  if(temp_status == 0) {
    srand(1);
  }
  
  next_temp = 99.15 + 5.5*sin(rand()%100);
  
  return next_temp;
}


int main() {
  srand(1);
  double next_temp;
  // we want to ensure that we get all of the tests we need.
  // 97.9 - 100.4 degrees Fahrenheit is typical for babies and children.
  // gives an average starting temperature of 99.15.
  bool temp_status;
  
  temp_status = get_command(next_temp);
  send_temperature(temp_status);
  
  
  return 0;
}
