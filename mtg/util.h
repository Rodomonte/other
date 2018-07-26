// UTIL

#ifndef util_h
#define util_h

#include "const.h"

int call(str cmd){
  int r;
  r = system(cmd);
  return (WIFEXITED(r) && !WEXITSTATUS(r)) ? 2 : 0;
}

bool in(str s, vs& v){
  int i;
  for(i = 0; i < v.size(); ++i)
    if(v[i] == s) return true;
  return false;
}

#endif
