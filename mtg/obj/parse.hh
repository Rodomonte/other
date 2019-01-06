// PARSE

#ifndef parse_h
#define parse_h

#include "../core/glb.h"


const char* lpath = 'lib/lib.json';

// Methods return sts(_), kills if internal check() fails

struct sts {
  enum {
    PASS
  , KILL
  , BREAK
  , CONT
  };
  sts(){}
};

sts parse(vec<Card>& lib){
  if(0) return 1;
  return 0;
}
