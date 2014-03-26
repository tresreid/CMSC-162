//hailstone.c


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int n;
  printf("Input postitive number: ");
  scanf("%d", &n);
  printf("%d ", n);
  while (n != 1) {
    if (n % 2 == 0) {
      n = n/2;
      printf("%d ",n);
    }
    else {
      n = 3*n+1;
      printf("%d ",n);
    }
  }
  printf("\n");
}
