%{
	// parse.y

#include <stdio.h>
#include <stdlib.h>

void yyerror(char *);
int yylex(void);

%}

%union {
	double mass;
	int count;
}

%token ERROR OPEN_PAREN CLOSE_PAREN EOLN EOFTOK
%token<mass> ELEMENT
%token<count> NUMBER

%type<mass> primary secondary compound

%start input

%%

input
	: lines EOFTOK				{ YYACCEPT; }
	;

lines
	:
	| lines line
	;

line
	: compound EOLN				{ printf("%f\n",$1); }
	| error EOLN				{ fprintf(stderr,"invalid\n"); }
	| EOLN
	;

primary
	: ELEMENT					{ $$ = $1; }
	| OPEN_PAREN compound CLOSE_PAREN
								{ $$ = $2; }
	;

secondary
	: primary					{ $$ = $1; }
	| primary NUMBER			{ $$ = $1 * $2; }
	;

compound
	: secondary					{ $$ = $1; }
	| compound secondary		{ $$ = $1 + $2; }
	;

%%

void yyerror(char *msg) {}

