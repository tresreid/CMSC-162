//array.c 

#include <stdio.h>
#include <stdlib.h>

int getValue( int* array, int numelems, int pos, int *value);

int main(int argc, char *argv[]){
  int position;
  int value;
  int arraysize = 0;
  int *array, *temparray;
  array = (int*) malloc(sizeof(int)*arraysize);
  do{
    puts("Enter a position (-1 and an arbitrary value to exit): ");
    scanf("%d", &position);
    puts("Enter a value: ");
    scanf("%d", &value);
    if (position >= arraysize){
      temparray = (int*)malloc(sizeof(int)*(position+1));
      memcpy(temparray, array,sizeof(int)*arraysize);
      free(array);
      arraysize = position+1;
      array = temparray;
      array[position] = value;
    }
    else{
      array[position] = value;
    }
  }while(position != -1);
  
  int k=0;
  while(k<arraysize){
    printf("%s","array[");
    printf("%d",k);
    printf("%s","] = ");
    if(!array[k]){
      puts("No value assigned");
      k++;
    }
    else{
      printf("%d\n", array[k]);
      k++;
	}
  }
  int access;
  puts("What position do you wish to acces? (-1 to quit): ");
  scanf("%d", &access);
  while(access != -1){
    int check = getValue(array, arraysize, access, &value);
    if(check == 0){
      printf("%s","array[");
      printf("%d",access);
      printf("%s","] is ");
      printf("%d\n", value);
    }
    else if(check == 1){
      puts("No value assigned");
    }
    else{
      puts("Out of bounds");
    }
    puts("What position do you wish to acces? (-1 to quit): ");
    scanf("%d", &access);
  }
}
int getValue( int* array, int numelems, int pos, int *value){
  if(pos< numelems){
   if(!array[pos]){
      return 1;
    }
    else{
      *value = array[pos];
      return 0;
    }
  }
  else{
    return 2;
  }
}
