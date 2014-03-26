%{ // para.y 
#include <stdio.h> 
#include <stdlib.h> 

void yyerror(char *); 
int yylex(void); 

%}
%union{
  int num;
 }
%token ERROR OPARA CPARA OBRAKET CBRAKET OSQIG CSQIG EOFTOK EOLN

%type<num> para
%start input

%% 

input
: lines EOFTOK  {YYACCEPT;}
;

lines
:
|lines line
;

line
:para EOLN {printf("%d\n", $1);}
|error EOLN {fprintf(stderr,"error\n");}
|EOLN
;

para
:OPARA CPARA  {$$ = 1;}
|OBRAKET CBRAKET{$$ = 1;}
|OSQIG CSQIG  {$$ = 1;}
|OPARA para CPARA {$$ = 1 + $2;}
|OBRAKET para CBRAKET {$$ = 1 + $2;}
|OSQIG para CSQIG  {$$ = 1 + $2;}
|para para {$$ = ($1 < $2) ? $2 : $1;}
;


%% 

void yyerror(char *msg) {}
