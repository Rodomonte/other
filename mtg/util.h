// UTIL

#ifndef util_h
#define util_h

#include "const.h"

bool in(str s, vs& v){
  int i;
  for(i = 0; i < v.size(); ++i)
    if(v[i] == s) return true;
  return false;
}

#endif
