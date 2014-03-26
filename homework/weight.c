//weight.c
#include <stdio.h>
#include "weight.h"
double weight (){
  double w;
  printf("Please input your weight(kg): ");
  scanf("%lf", &w);
  return w;
}
