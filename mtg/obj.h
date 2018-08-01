// OBJ

#ifndef obj_h
#define obj_h

#include "global.h"


struct str : string {
  bool in(vs& v){
    int i;
    for(i = 0; i < v.size(); ++i)
      if(v[i] == *this) return true;
    return false;
  }

  bool in(umap<str, Card> m){
    umap<str, Card>::iterator it;
    for(it = m.begin(); it != m.end(); ++it)
      if(it->first == *this) return true;
    return false;
  }
};

struct Obj {
  virtual map<str, str> to_map();

  str to_str(){
    str s;
    map<str, str> m;
    map<str, str>::iterator it;

    m = to_map();
    for(it = m.begin(); it != m.end(); ++it){
      sprintf(buf, "%s: %s\n", it->first.c_str(), it->second.c_str());
      s += str(buf);
    }
    return s;
  }
};


#endif
