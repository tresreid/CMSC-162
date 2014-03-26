//queue.c
//not the most effecient method but it works well.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[]){
  char *filename;
  char *line = NULL;
  size_t len =0;
  ssize_t read;
  int arraysize = 0;
  FILE *infile = fopen(argv[1], "r");
  FILE *checkfilesize = fopen(argv[1], "r");
  if (infile == NULL){
    printf("Could not open file yo \n");
    fclose(infile);
    exit(-1);
  }
  //allows for the number of total lines to be counted
  while ((read = getline(&line, &len, checkfilesize) != -1)){
    arraysize ++;
  }
  double arrival[arraysize];
  double servicetime[arraysize];
  int i =0;
  while ((read = getline(&line, &len, infile) != -1)){
      char *innum = strtok(line, " ");
      char *time = strtok(NULL, " ");
      arrival[i]= (double) atoll(innum);
      servicetime[i] = (double) atoll(time);
      i++;
  }
  int j = 0;
  int k=0;
  double timer=0.00;
  double queue[arraysize];
  int queueSize = 0;
  int maxSize=0;
  float depart[arraysize];
  while((timer <= arrival[arraysize-1]) || (queueSize >0) ){
    //increment the timer by .01 intervals since all input is to 2 decimal places 
    timer += 0.01;
    //departures are done first
    if(queueSize >0){
      //going throw service time for the front person
      queue[0] = queue[0] - 0.01;
      //departure
      if(queue[0] <= 0.00){
	int l =0;
	while(l<queueSize){
	  queue[l] = queue[l+1];
	  l++;
	}
	queueSize -= 1;
	depart[k] = timer;
	k++;
      }
    }
    //arrival
    if((timer >= arrival[j]) && (j<arraysize)){
      //adds to queue
      queue[queueSize] = servicetime[j];
      queueSize += 1;
      j++;
      //checks max size
      if(queueSize > maxSize){
	maxSize = queueSize;
      }
    }
  }
  int m=0;
  int maxtime=0;
  //finds max wait time
  while(m<k){
    if(maxtime < (depart[m]-arrival[m])){
      maxtime = (depart[m] - arrival[m]);
    }
    m++;
  }
  printf("Max queue size: %d\n", maxSize);
  printf("Max wait time: %d\n", maxtime);
  if(line)
    free(line);
  fclose(infile);
  exit(0);
}
