// atomic-weight.c
// © 2005 Stuart A. Kurtz
// Top level code for atomic-weight calculator

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>

#include "element-db.h"

element_db db;
char *progname;

int yylex(void);
int yyparse(void);
void parse_string(char *str);

int main(int argc, char **argv) {
	progname = argv[0];

	char *data_file = "~/.mass_data";

	db = create_element_db(data_file);
	
	if (argc > 1) {
		for (int i = 1; i < argc; ++i) {
			parse_string(argv[i]);
		}
	} else {
		yyparse();
	}

	delete_element_db(&db);
	exit(0);
}

