// OBJ

#ifndef obj_h
#define obj_h

#include "card.h"

struct Deck {
  str name;
  vec<Card> main, side, extra;
  Deck(vec<Card> _main, vec<Card> _side, vec<Card> _extra):
    main(_main), side(_side), extra(_extra) {}

  void print(){
    int i;
    map<string, int> m;
    map<string, int>::iterator it;

    for(i = 0; i < main.size(); ++i){
      if((it = m.find(main[i].name)) == m.end())
        m[main[i].name] = 1;
      else ++it->second;
    }

    printf("%s:\n", name.c_str());
    for(i = 0; i < main.size(); ++i)
      printf("%dx ", m[main[i].name]);
      main[i].print();
      printf("\n");
  }
};

#endif
