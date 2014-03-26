%{ 
// prop_formula.y 
// parsing for boolean expressions 
%}

%token AND OR IMPLIES NOT OPEN_PAREN CLOSE_PAREN VAR 

%% 


imp
:intersec
|intersec IMPLIES imp
;

intersec
:unions
|intersec OR unions
;

unions
:neg
|unions AND neg
;

neg
:quantity
|NOT neg
;

quantity
:VAR
|OPEN_PAREN quantity CLOSE_PAREN
;
%%
