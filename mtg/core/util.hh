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
};

void check(stat s){ if(s == KILL) kill(); }

stat call(str& cmd){
  int r;
  r = system(cmd);
  return (WIFEXITED(r) && !WEXITSTATUS(r)) ? PASS : KILL;
}


#endif
