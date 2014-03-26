// element-db.c
// Copyright 2005, 2006 Stuart A. Kurtz
// Element database

// We assume that the datafile consists of a sequence of lines giving
// an element's atomic number, abbreviation, mass, and full name, e.g.,
//    1  H   1.00794      Hydrogen
//    2  He  4.002602     Helium
//    ...

// Our in-memory database is a linked list, with sequential access.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "atomic-weight.h"
#include "element-db.h"

element_db create_element_db(char *file_name) {
	char abbrev_buf[4];
	char element_buf[128];
	int number;
	double mass;
	
	element_ptr result = NULL;
	element_ptr *next_ptr = &result;

	char *cmd;
	asprintf(&cmd,"sed -e 's/#.*//' -e '/$[ \t]*^/d' < %s\n",file_name);
	if (cmd == NULL) {
		fprintf(stderr,"%s (%s:%d) -- malloc failure\n",progname,__FILE__,__LINE__);
		exit(-1);
	}

	FILE *data = popen(cmd,"r");
	if (data == NULL) {
		fprintf(stderr,"%s (%s:%d) -- popen failure\n",progname,__FILE__,__LINE__);
		exit(-1);
	}

	free(cmd);
	int fscanf_result;

	while ( (fscanf_result =
				fscanf(data,"%d %s %lf %s",&number, abbrev_buf, &mass, element_buf))
			 == 4 ) {
		element_ptr next = (element_ptr) malloc(sizeof(element_record));
		if (next == NULL) {
			fprintf(stderr,"%s (%s:%d) -- malloc failure\n",progname,__FILE__,__LINE__);
			exit(-1);
		}
		next->next = NULL;
		next->abbrev = strdup(abbrev_buf);
		next->name = strdup(element_buf);
		next->atomic_number = number;
		next->mass = mass;
		*next_ptr = next;
		next_ptr = &next->next;
	}
	if (fscanf_result != EOF) {
		fprintf(stderr,"%s (%s:%d) -- improperly formatted database file %s\n",
				progname,__FILE__,__LINE__,file_name);
		exit(-1);
	}
	pclose(data);
	return result;
}

const element_ptr lookup_element(element_db db, char *abbrev) {
	for (element_ptr current = db; current != NULL; current = current->next) {
		if (strcmp(abbrev,current->abbrev) == 0) {
			return current;
		}
	}
	return NULL;
}

void delete_element_db(element_db *db) {
	element_ptr current = *db;
	
	while (current != NULL) {
		free(current->abbrev);
		free(current->name);
		element_ptr next = current->next;
		free(current);
		current = next;
	}
	
	*db = NULL;

	return;
}
