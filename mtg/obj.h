// OBJ

#ifndef obj_h
#define obj_h

#include "global.h"


struct str : string {
  bool in(str& s){
    int i, j;
    for(i = 0; i < s.size(); ++i){
      for(j = 0; j < this->size(); ++j){
        if(i+j >= s.size()) return false;
        if(s[i] != (*this)[j]) break;
        if(j == this->size()-1) return true;
      }
    }
    return false;
  }

  bool in(vs& v){
    int i;
    for(i = 0; i < v.size(); ++i)
      if(v[i] == *this) return true;
    return false;
  }

  bool in(umap<str, Card>& m){
    umap<str, Card>::iterator it;
    for(it = m.begin(); it != m.end(); ++it)
      if(it->first == *this) return true;
    return false;
  }

  str strip_front(str& strips){
    int i;
    for(i = 0; i < this->size() && str((*this)[i])->in(strips); ++i);
    return this->substr(i, this->size()-i);
  }
  str strip_end(str& strips){
    int i;
    for(i = this->size()-1; i >= 0 && str((*this)[i])->in(strips); --i);
    return this->substr(0, i+1);
  }
  str strip(str& strips){
    return this->strip_front(strips).strip_end(strips);
  }

  str join(str& s){
    return this->strip_end("/") + "/" + s.strip_front("/");
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
