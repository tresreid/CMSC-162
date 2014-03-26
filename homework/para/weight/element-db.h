#ifndef GUARD_ELEMENT_DB
#define GUARD_ELEMENT_DB

// element-db.h
// © 2005, 2011 Stuart A. Kurtz
// Interface to the element database

typedef struct element_record {
	struct element_record *next;
	char *abbrev;
	char *name;
	int atomic_number;
	double mass;
} element_record, *element_ptr, *element_db;;

element_db create_element_db(char *file_name);
const element_ptr lookup_element(element_db, char *abbrev);
void delete_element_db(element_db *db);

#endif
