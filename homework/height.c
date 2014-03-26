//height.c
#include <stdio.h>
#include "height.h"
double height(){
  double h;
  printf("Please enter your height(m): ");
  scanf("%lf", &h);
  return h;
}
