// dict.c
// Hash-based dictionary.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "dict.h"
#include "hash.h"

void histogram(dict_type *d);

void dict_initialize(dict_type *d) {
    dict_cell **dp = d->contents;
    for (int i = 0; i < DICT_SIZE; ++i) {
        dp[i] = NULL;
    }
}

void dict_increment(dict_type *dp, char *word){
    dict_cell **bp = &dp->contents[hash(word) & DICT_MASK];
    
    while(*bp != NULL && strcmp((*bp)->entry.word,word)) {
        bp = &(*bp)->next;
    }
    
    if (*bp == NULL) {
        // allocate a new cell...
    
        (*bp) = (dict_cell *) malloc (sizeof(dict_cell));
        assert(*bp != NULL);
        
        (*bp)->next = NULL;
        (*bp)->entry.word = strdup(word);
        (*bp)->entry.count = 0;
    }
    
    ++(*bp)->entry.count;
    
    return;
}

static int de_compare(const void *a, const void *b) {
	dict_entry_type *ap = * (dict_entry_type **)a;
	dict_entry_type *bp = * (dict_entry_type **)b;
	int diff = bp->count - ap->count;
	if (diff != 0) {
	    return diff;
	}
	return strcmp(ap->word,bp->word);
}


void histogram(dict_type *d) {

  int* result;
  int count = 0;
  int max_count =0;
  int bucket_size =0;
  int nonempty =0;
  int index;

  for(int i =0; i< DICT_SIZE; ++i){
    int bucket_size =0;

    dict_cell *dcp = d -> contents[i];

    while (dcp != NULL){
      ++count;
      ++bucket_size;
      dcp = dcp -> next;
    }

    if (max_count < bucket_size) max_count = bucket_size;
    if (bucket_size != 0) nonempty +=1;
  }

  result = (int*) calloc(max_count +1, sizeof(int));
  
  for (int i =0; i < DICT_SIZE; ++i){
    int bucket_size =0;
    dict_cell *dcp = d -> contents[i];

    while(dcp != NULL){
      ++bucket_size;
      dcp = dcp->next;
    }
    result[bucket_size] +=1;
  }

  printf("max bucket size: %d\n", max_count);
  printf("number of nonempty buckets: %d\n", nonempty);
  printf("average non empty bucket size: %f\n", (float) count/nonempty);

  printf("Frequency table: \n");
  printf("bucket size \t frequency\n");
  for (int i = 0; i<= max_count; ++i) printf("%d\t\t%d\n",i, result[i]);
  
  printf("| = 100, * = 10, numerical values are 1 digit values");
  
  for(int i =0; i<= max_count; ++i){
    printf("%d\t",i);
    for (int index = 1; index*100 <= result[i]; ++index) printf("|");
    for (int index = 1; index*10 <= result[i]%100; ++index) printf("*");
    if(result[i] >= 10) printf(" + %d\n", result[i] %10);
    else printf("%d\n", result[i]);
  }
}
dict_entry_type **dict_get_entries(dict_type *d) {
	// count the entries...
	
	int count = 0;
	
	for (int i = 0; i < DICT_SIZE; ++i) {
	    // traverse bucket i
	    
	    dict_cell *dcp = d->contents[i];
	    
	    while (dcp != NULL) {
	        ++count;
	        dcp = dcp->next;
	    }
	}
	
	
	dict_entry_type **result = (dict_entry_type **) calloc(count+1,sizeof(dict_entry_type *));
	assert(result != NULL);
    
	int index = 0;
	
	// load the entries
	
	for (int i = 0; i < DICT_SIZE; ++i) {
	    dict_cell *dcp = d->contents[i];
	    
	    while (dcp != NULL) {
	        result[index++] = &dcp->entry;
	        dcp = dcp->next;
	    }
	}
	
	assert(index == count);
	result[index] = NULL;
	
	qsort((void*) result, count, sizeof(dict_entry_type *),de_compare);
	
	return result;
}


			 
