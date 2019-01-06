// DECK

#ifndef deck_h
#define deck_h

#include "card.h"


struct Deck {
  int       id;
  Format    format;
  str       name;
  vc main, side, extra;

  Deck(int _id, Format _format): id(_id), format(_format) {}
  Deck(vc _main, vc _side, vc _extra):
    main(_main), side(_side), extra(_extra) {}

  str file(){ return str(sprintf("%s/d%4d.deck", DECK_DIRS[format], id)); }

  void from_str(str& s){

  }

  void from_file(){
    str s;

  }

  str to_str(){
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

  void to_file(){
    FILE* fp;
    fp = fopen(file().c_str(), "w");
    fprintf(
  }
};


#endif
