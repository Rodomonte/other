// OBJ

#ifndef obj_h
#define obj_h

//#include


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
