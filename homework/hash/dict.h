// freq.h

#ifndef FREQ_H
#define FREQ_H

#define DICT_BITS 17
#define DICT_SIZE (1 << 16)
#define DICT_MASK (DICT_SIZE-1)


typedef struct {
    char *word;
    int count;
} dict_entry_type;

typedef struct dict_cell {
    struct dict_cell *next;
    dict_entry_type entry;
} dict_cell;

typedef struct {
    dict_cell *contents[DICT_SIZE];
} dict_type;

void dict_initialize(dict_type *d);
void dict_increment(dict_type *d, char *word);

dict_entry_type **dict_get_entries(dict_type *d);

#endif
