//power.c

#include <stdio.h>
#include <string.h>
#include "power.h"
// source: http://en.wikipedia.org/wiki/Exponentiation_by_squaring
//changed to unsigned type 
unsigned power(unsigned y,unsigned m){
  // if the exponent is 0
  if(m == 0){
    return 1;
  }
  // if the exponent is 1 return the base. ends the recursion
  else if (m==1){
    return y;
  }
  //for even exponents 
  else if ((m % 2) == 0){
    return power(y*y, m/2);
  }
  //for odd exponents
  else if ((m % 2) == 1){
    return y * power(y*y, (m-1)/2);
  }
}
 
 
