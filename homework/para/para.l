%{
#include <stdio.h>

int yyparse();
%}

%option noyywrap


%%

\(    {return OPARA;}
\)    {return CPARA;}
\[    {return OBRAKET;}
\]    {return CBRAKET;}
\{    {return OSQIG;}
\}    {return CSQIG;}

.     {return ERROR;}
\n    {return EOLN;} 
<<EOF>> {return EOFTOK;}
%%