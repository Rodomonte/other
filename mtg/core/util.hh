// UTIL

#ifndef util_h
#define util_h

#include "const.h"


// Globals

char buf[1048576]
   , err[2048];


#define kill() quit(__FILE__, __FUNCTION__);

#define check(r) if(r == PASS) {} \
            else if(r == 2) break; \
            else if(r == 3) continue; \
            else            kill();


void quit(const char* file, const char* fn){
  printf("Exiting from %s::%s\n", file, fn);
  exit(0);
}

int call(str& cmd){
  int r;
  r = system(cmd);
  return (WIFEXITED(r) && !WEXITSTATUS(r)) ? 2 : 0;
}


#endif
