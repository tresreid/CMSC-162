// Top level code for atomic-weight calculator

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>

char *progname;

int yylex(void);
int yyparse(void);

int main(int argc, char **argv) {
	yyparse();
	exit(0);
}
