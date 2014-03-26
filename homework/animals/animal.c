//Michael Reid
// animal.c

//Not all the code belongs to me. Used an online resource  
//Source : http://www.planet-source-code.com/vb/scripts/ShowCode.asp?txtCodeId=6232&lngWId=3

#include<stdio.h>
#include<string.h>
#include<ctype.h>

struct Animal
{
  char data[50];
  struct Animal* left;
  struct Animal* right;
  struct Animal* parent;
};

#define FLUSH while (getchar() != '\n')	 
void push(struct Animal*[], int*, struct Animal*);
struct Animal* pop(struct Animal*[], int*);
struct Animal* build_tree(int*);
//void print_file(struct Animal*, int*);
struct Animal* user_play(struct Animal*, int*);
int valid_char(char[]);
int question_check(char[]);


int main(void)
{
  struct Animal* current;
  struct Animal* temp_root;
  int n=0;

  current= build_tree(&n);							
  temp_root= current;									
  temp_root= user_play(temp_root,&n); 
  print_file(temp_root, &n);	
  return 0; 
}
// makes sure the user inputs only Y/N to avoid an error. return of 1 is correct use. 
int valid_char(char m[])
{
  int x,flag=0;									
  x= strlen(m); 
  if(x>1)											
    flag=0;
  else
    {
      if(m[0]=='y'|| m[0]=='Y')
	flag=1;
      if(m[0]=='n'|| m[0]=='N')
	flag=1;
    }
  return flag;
}
//checks for a question mark to see if the input is a question.
int question_check(char n[])
{
  int x, flag=0;
  x= strlen(n);
  if(n[x-2]=='?')										
    flag=1;
  return flag;
}

//If not full, the pointer is inserted into its appropriate slot of the stack.
void push(struct Animal* stack[], int* top, struct Animal* current)
{												
  if(*top<99)											
    {												
      (*top)++;
      stack[*top]= current;							
    }
  else
    printf("\nThe stack is full.");
}


//If not empty, a pointer is then returned to main.
struct Animal* pop(struct Animal* stack[], int* top)
{
  struct Animal* temp;								
  if(*top==-1)										
    printf("\nThe stack is empty.");				
  else
    {
      temp= stack[*top];							
      (*top)--;
    }
  return temp;
}

struct Animal* build_tree(int *node_count)
{
  FILE *fin;
  char move[6], temp_info[50];
  struct Animal* current;
  struct Animal* temp;
  struct Animal* head;
  int a, count=0, r=0, i;
  struct Animal* stack[100];
  //The file is opened for reading in the program, a file pointer is declared.
  fin= fopen("c:\\work\\input.txt","r");	
  //move is initialized to left.
  strcpy(move,"left");							
  //scans in the first string from the file, places it in variable.
  fgets(temp_info, sizeof(temp_info), fin);
  //The root node is created and info is placed in it			
  current= malloc(sizeof(struct Animal));								
  strcpy(current->data, temp_info);
  current->left= NULL;
  current->right= NULL;
  current->parent= NULL;
  temp= current;
  head= current;
  (*node_count)++;
  
  while(!feof(fin))    
    {
      fgets(temp_info, sizeof(temp_info), fin);				
      a= strlen(temp_info);
      //If move is equal to left, then it is a question
      if(strcmp(move,"left")==0)								 
	{													
	  push(stack, &r, current);
	  current->left= malloc(sizeof(struct Animal));
	  current= current->left;
	  strcpy(current->data, temp_info);
	  current->left= NULL;
	  current->right= NULL;
	  current->parent= temp;
	  (*node_count)++;
	}
      //If move is equal to right, then the stack is popped to the previous pointer.
      else
	{
	  current= pop(stack, &r);							
	  current->right= malloc(sizeof(struct Animal));
	  current= current->right;
	  strcpy(current->data, temp_info);
	  current->left= NULL;
	  current->right= NULL;
	  current->parent= temp;
	  (*node_count)++;
	}
      
      count=0;
      //determines whether the string is a question.
      for(i=0;i<a;i++)										
	{
	  if(temp_info[i]=='?')
	    {
	      count++;
	    }
	}
      //If it is a question, then move is equal to left, else, move is right.
      if(count>0)				
	strcpy(move,"left");
      else
	strcpy(move,"right");
    }
  fclose(fin);												
  return head;											     
}

struct Animal* user_play(struct Animal* temp_root, int *node_count)
{
  struct Animal* current;
  struct Animal* temp;
  char ques_choice, ans_choice, answer, game_choice;
  int count1=0, count_wrong=0, i;
  char b[50], x[50], temp_answer[50], new_question[50], new_answer[50]; 
  char move[6], game_choice1[20], answer1[20], ques_choice1[20], ans_choice1[20];
  
  do
    {
      printf("\nWould you like to play the animal guessing game?");	  
      printf("\nPress 'Y' to continue, 'N' to QUIT:    ");			
      scanf("%s", &game_choice1);
    }while(valid_char(game_choice1)==0);
  
  game_choice= game_choice1[0];  
  FLUSH;
  
  while(game_choice=='y' || game_choice=='Y')
    {
      current= temp_root;
      printf("\nFor the following questions, Press 'Y' for yes, 'N' for no.");
      do
	{
	  printf("\n\n%s", current->data);						      
	  scanf("%s", &ques_choice1);
	}while(valid_char(ques_choice1)==0);
      
      ques_choice= ques_choice1[0];
      FLUSH;
      
      if(ques_choice=='y' || ques_choice=='Y')
	strcpy(move,"left");
      else
	strcpy(move,"right");
      
      while(current!=NULL)	     
	{
	  count1=0;
	  count_wrong=0;
	  
	  if(strcmp(move,"left")==0)
	    {
	      current= current->left;
	      strcpy(x, current->data);
	      //checks for a question
	      for(i=0;i<(strlen(x));i++)
		{
		  if(x[i]=='?')			    
		    count1++;
		}
	      
	      if(count1>0)
		{
		  do
		    {
		      printf("%s", current->data);
		      scanf("%s", &ques_choice1);
		    }while(valid_char(ques_choice1)==0);
		  
		  ques_choice= ques_choice1[0];
		  //If it is a question, move = right, else, move = left.
		  FLUSH;						
		  
		  if(ques_choice=='y' || ques_choice=='Y')
		    strcpy(move,"left");
		  else
		    strcpy(move,"right");
		}
	      else
		{
		  //The program makes a guess when it comes to a leaf.
		  printf("\nI would like to make a guess. You are a(n) %s", current->data);	
		  
		  do
		    {
		      printf("\nPRESS 'Y' if I guessed right, PRESS 'N' if I was wrong:  ");
		      scanf("%s",&ans_choice1);
		    }while(valid_char(ans_choice1)==0);
		  
		  ans_choice= ans_choice1[0];
		  FLUSH;
		  	//After it makes a guess, it breaks the while loop by assigning current to NULL.
		  if(ans_choice=='y' || ans_choice=='Y')
		    current= NULL;
		  else
		    {
		      temp= current;
		      current= NULL;
		      count_wrong++;
		    }
		}
	    }
	  //else statement is for if move was equal to right. It dos the same as left.
	  else											
	    {
	      current= current->right;
	      strcpy(b, current->data);
	      for(i=0;i<(strlen(b));i++)
		{
		  if(b[i]=='?')
		    count1++;
		}
	      
	      if(count1>0)
		{
		  do
		    {
		      printf("%s", current->data);
		      scanf("%s", &ques_choice1);
		    }while(valid_char(ques_choice1)==0);
		  
		  ques_choice= ques_choice1[0];
		  FLUSH;
		  
		  if(ques_choice=='y' || ques_choice=='Y')
		    strcpy(move,"left");
		  else
		    strcpy(move,"right");
		}
	      else
		{
		  printf("\nI would like to make a guess. You are a(n) %s", current->data);
		  
		  do
		    {
		      printf("\n\nPRESS 'Y' if I guessed right, PRESS 'N' if I was wrong:  ");
		      scanf("%s",&ans_choice1);
		    }while(valid_char(ans_choice1)==0);
		  
		  ans_choice= ans_choice1[0];
		  FLUSH;
	     
		  if(ans_choice=='y' || ans_choice=='Y')
		    current= NULL;
		  else
		    {
		      temp= current;
		      current= NULL;
		      count_wrong++;
		    }
		}
	    }
	}
      //If the program guessed wrong, the user inputs thier info into the new nodes which are created.
      if(count_wrong>0)			
	{															
	  current= temp;										
	  current->left= malloc(sizeof(struct Animal));
	  (*node_count)++;
	  current->right= malloc(sizeof(struct Animal));
	  (*node_count)++;
	  strcpy(temp_answer, current->data);
	  
	  do
	    {
	      printf("\nPlease enter a question to distinguish your animal.");
	      printf("\n( be sure to include a question mark ).\n");
	      fgets(new_question,sizeof(new_question),stdin);
	    }while(question_check(new_question)==0);	//Determines if they put a question mark.
	  
	  strcpy(current->data, new_question);
	  printf("\nWhat type of animal are you?\n");
	  fgets(new_answer,sizeof(new_answer),stdin);
	  
	  do
	    {
	      printf("\nIs your answer correct for your question?  Type 'Y' for yes, 'N' for no:   ");
	      scanf("%s",&answer1);
	    }while(valid_char(answer1)==0);
	  
	  answer= answer1[0];
	  //Determines whether their answer is correct to their question.
	  if(answer=='y' || answer=='Y')							
	    {													
	      current= current->left;
	      current->parent= temp;
	      strcpy(current->data, new_answer);
	      current->left= NULL;
	      current->right= NULL;
	      current= temp;
	      strcpy(current->data,new_question);
	      current= current->right;
	      current->parent= temp;
	      strcpy(current->data, temp_answer);
	      current->left= NULL;
	      current->right= NULL;
	    }
	  else
	    {
	      current= current->right;
	      current->parent= temp;
	      strcpy(current->data, new_answer);
	      current->left= NULL;
	      current->right= NULL;
	      current= temp;
	      strcpy(current->data,new_question);
	      current= current->left;
	      current->parent= temp;
	      strcpy(current->data, temp_answer);
	      current->left= NULL;
	      current->right= NULL;
	    }
	}
      do
	{
	  printf("\nWould you like to play again?:   ");
	  printf("\nPress 'Y' to continue, 'N' to QUIT:    ");			
	  scanf("%s", &game_choice1);
	}while(valid_char(game_choice1)==0);
      
      game_choice= game_choice1[0];
      FLUSH;
		
    }
  
  printf("\nThank you for playing.");
  current= temp_root;  
  return current;
}

