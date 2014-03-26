//guess.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[]){
  int target1;
  int guess;
  int limit;
  int cap = -1;
  char *dif;
  if(argc == 1){
    limit = 100;
  }
  else if(argc == 2){
    if(strcmp(argv[1],"-n")==0 ){
      sscanf(argv[2],"%d", &limit);
    }
    else if(strcmp(argv[1],"-d")==0 ){
      sscanf(argv[2],"%s", &*dif);
      limit = 100;
      if((strcmp(*dif,"easy")==0)){
	cap = 0.8 * (log(limit) / log(2));
      }
      else if(strcmp(*dif,"medium")==0){
	cap = 0.6 * log(limit) / log(2);
      }
      else if(strcmp(dif,"hard")==0){
	cap = 0.4 * log(limit) / log(2);
      }
      else if(strcmp(dif,"unlimited")==0){
	cap = -1;
      }
    }
  }
  else{
    if((strcmp(argv[1],"-n")==0) || (strcmp(argv[2],"-n")==0)){
      sscanf(argv[2],"%d", &limit);
    }
    else if((strcmp(argv[1],"-d")==0) ||(strcmp(argv[1],"-d")==0)){
      sscanf(argv[2],"%s", &*dif);
      if((strcmp(*dif,"easy")==0)){
	cap = 0.8 * (log(limit) / log(2));
      }
      else if(strcmp(*dif,"medium")==0){
	cap = 0.6 * log(limit) / log(2);
      }
      else if(strcmp(dif,"hard")==0){
	cap = 0.4 * log(limit) / log(2);
      }
      else if(strcmp(dif,"unlimited")==0){
	cap = -1;
      }
    }
    else{
      limit = 100;
    }
  }
 
  srand(time(NULL));
  target1 = rand() % limit +1;
  do{
    puts("guess a number: ");
    scanf("%d", &guess);
    if(guess < target1){
      puts("Too Low");
      cap--;
    }
    else if(guess > target1){
      puts("too high");
      cap--;
    }
  } while( (target1 != guess) && (cap != 0));
  puts ("You got it");
  return 0;
}
