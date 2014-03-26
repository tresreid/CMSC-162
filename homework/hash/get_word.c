// get_word.c

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_word.h"

char *get_word(FILE *fp) {
    static char *buf = NULL;
    static int buf_size = 0;
    
    // allocate our input buffer

    if (buf == NULL) {
        buf_size = 256;
        buf = (char *) calloc(buf_size,sizeof(char));
        assert(buf != NULL);
    }
    
    int ch;
    
    // scan past any white space.

    while (!isalpha(ch = fgetc(fp)))    {
        if (ch == EOF)
            return NULL;
    }
    
    // read the word
    
    int index = 0;
    do {
        // invariants:
        //  index &lt; buf_size
        //  buf points to a buffer of size buf_size
        //  ch contains the next character to be added to the buffer

        buf[index++] = (char) tolower(ch);

        // make sure we can push another character,
        // reallocating the buffer if necessary.
        
        if (index == buf_size) {
            buf_size *= 2; 
            buf = realloc(buf,buf_size * sizeof(char));
            assert(buf != NULL);
       }
        
        
    } while (isalpha(ch = fgetc(fp)) && ch != EOF);
    
    buf[index] = 0;
    
    return buf;

}
