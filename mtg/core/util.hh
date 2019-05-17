// UTIL

#ifndef util_hh
#define util_hh

#include "const.hh"


char buf[64000000]
   , err[2048];


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

stat call(const char* cmd){
  int r;
  r = system(cmd);
  return (WIFEXITED(r) && !WEXITSTATUS(r)) ? PASS : KILL;
}

bool in(str& s, uset<str>& u){
  return u.find(s) != u.end();
}


#endif
