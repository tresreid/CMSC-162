// hist.c

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <libgen.h>

#include "dict.h"
#include "get_word.h"

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr,"usage: %s file\n",basename(argv[0]));
		exit(-1);
	}
	
	FILE *input = fopen(argv[1],"r");
	if (input == NULL) {
		fprintf(stderr,"fatal error -- could not open input (%s)\n",argv[1]);
		exit(-1);
	}
	
	dict_type dict;
	dict_initialize(&dict);
	
	char *word = NULL;
	while ((word = get_word(input))) {
		dict_increment(&dict,word);
	}
	
	dict_entry_type **entries = dict_get_entries(&dict);
	
	for (int i = 0; entries[i] != NULL; ++i) {
	  histogram(entries);
	}
	
	exit(0);
}

