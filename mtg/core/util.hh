// UTIL

#ifndef util_hh
#define util_hh

#include "const.hh"


// Globals

char buf[1048576]
   , err[2048];

vec<Card> lib;
vec<Deck> decks;


// Methods

void quit(const char* file, const char* fn){
  printf("Exiting from %s::%s\n", file, fn);
  exit(0);
}

#define kill() quit(__FILE__, __FUNCTION__);

enum stat {
  KILL
, BACK
, PASS
, CONT
, BREAK
};

#define check(r) if(r == KILL) kill(); \
            else if(r == BACK) return; \
            else if(r == PASS) {} \
            else if(r == CONT) continue; \
            else if(r == BREAK) break;

stat call(str& cmd){
  int r;
  r = system(cmd);
  return (WIFEXITED(r) && !WEXITSTATUS(r)) ? PASS : KILL;
}


#endif
