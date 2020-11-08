#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

bool get_command(next_temp) {  
  <<next_temp;
  >>temp_status;
  //This will send the temp data to the server
  //And recieve the status from the server  
  return temp_status;    
}

double send_temperature(bool temp_status) {
  if(temp_status == 0) {
    srand(1);
  }
  
  next_temp = 99.15 + 5.5*sin(rand()%100);
  //Based on the status of the temperature previously
  //Either the temp will continue to fluctuat as normal
  //Or it will be reset to 99.15 if it is out of bounds
  return next_temp;
}

int end(){
  >>x
    //This function allows us to end the program's loop
    //Through an imput from the server
    return x;
}
  

int main() {
  srand(1);
  int x = 0;
  
  while (x == 0){
  double next_temp;
  // we want to ensure that we get all of the tests we need.
  // 97.9 - 100.4 degrees Fahrenheit is typical for babies and children.
  // gives an average starting temperature of 99.15.
  bool temp_status;
  
  temp_status = get_command(next_temp);
  send_temperature(temp_status);
   
    pause(2);
  x = end();
  }
  
  return 0;
}
