#include <stdio.h>
#include <stdlib.h>

void greet(char *user);

int main(int argc, char **argv){
  greet(getenv("USER"));
  exit(0);
}

void greet(char *user){
  printf("Hello, %s!\n", user == NULL ? "world" : user);
  return;
}
