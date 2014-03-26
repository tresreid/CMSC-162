%{
/* decomment.l 
 * remove comments from C source files. 
 */ 
#include <stdio.h> 
#include <stdlib.h> 
%} 
%option noyywrap 
%x COMMENT 
%x SKIP
%x SKIPNEXT
%% 
<INITIAL>"\"" {
 /* skip over string literals */
 putchar(yytext[0]);
BEGIN SKIP;
 }
<INITIAL>"/*" { 
/* Match the beginning of a multi-line comment */ 
BEGIN COMMENT; 
} 
<INITIAL>"//".* { 
/* Match a single-line comment */ 
}
<INITIAL>.|\n { 
 putchar(yytext[0]); 
} 
<SKIPNEXT>. {
// Skips escape characters
putchar(yytext[0]);
BEGIN SKIP;
}
<SKIP>"\\" {
//skips escape characters
putchar(yytext[0]);
BEGIN SKIPNEXT;
}
<SKIP>"\"" {
//ends string literal
 putchar(yytext[0]);
BEGIN INITIAL;
}
<SKIP>. {
//prints string literal
putchar(yytext[0]);
}

<COMMENT>"*/" { 
/* Recognize the end of a comment */ 
BEGIN INITIAL; 
} 
<COMMENT>. { 
/* Dispense with characters in multi-line comments */ 
} 
<COMMENT>\n { 
putchar('\n'); 
} 

%% 

int main (int argc, char **argv) { 
yylex(); 
exit(0); 
}