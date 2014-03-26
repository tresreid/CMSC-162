//bmi.c
#include <stdio.h>
#include "height.h"
#include "weight.h"

int main(void){
  double h= height();
  double w= weight();
  double bmi = w/ (h*2);
  printf("Your bmi index is: %lf\n", bmi);
  return 0;
}
