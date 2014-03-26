// rotfile.c 
// Apply rot13 coding to the files given on the command line. 
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <fcntl.h> 
#include <sys/mman.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>

#ifdef Darwin 
#define BSD 
#endif 

#ifndef BSD 
#include <sys/file.h> 
#endif 

char rmap[256]; 
// open and immediately lock a file 
int lopen(char *path, int oflags) {
#ifdef BSD 
  return open(path,oflags | O_EXLOCK,0); 
#else 
  int filedes = open(path,oflags,0); 
  if (filedes == -1) 
    return filedes; 
  if (flock(filedes,LOCK_EX | LOCK_NB) != 0) { 
    fprintf(stderr,"Could not obtain lock on %s.\n",path); 
    close(filedes); 
    return -1; 
  }
  return filedes; 
#endif 
} 
int main(int argc, char **argv) { 
  // set up the rmap array 
  size_t page_size = (size_t) sysconf(_SC_PAGESIZE);
  for (int i = 0; i < 256; ++i) { 
    if (islower(i)) { 
      rmap[i] = (i - 'a' + 13) % 26 + 'a'; 
    } 
    else if (isupper(i)) { 
      rmap[i] = (i - 'A' + 13) % 26 + 'A'; 
    }
    else { 
      rmap[i] = i; 
    }
  }
  // process input 
  for (int i = 1; i < argc; ++i) {
    int filedes = lopen(argv[i],O_RDWR); 
    if (filedes == -1) { 
      fprintf(stderr,"Could not open locked file %s.\n",argv[i]); 
      continue; 
    }
    struct stat statbuf; 
    fstat(filedes,&statbuf);
    off_t offset=0;
    size_t chunk = page_size;
    char *buf;
    do{
      if((offset + chunk) > statbuf.st_size){
	buf = (char *) mmap(NULL,statbuf.st_size,PROT_READ|PROT_WRITE, MAP_SHARED,filedes,offset); 
      }
      else{
	buf = (char *) mmap(NULL,chunk,PROT_READ|PROT_WRITE, MAP_SHARED,filedes,offset);
      }
      if (buf == (char *) -1) { 
	fprintf(stderr,"Memory mapping failed on %s\n",argv[i]); 
	perror(NULL); 
	close(filedes);
	continue; 
      } 
      char *cp = buf; 
      char *endp = buf + statbuf.st_size; 
      while (cp != endp) { 
	*cp = rmap[*cp]; ++cp; 
      }
      offset += chunk;
      munmap(buf,statbuf.st_size); 
    }while(offset< statbuf.st_size);
    close(filedes); 
  }
}

