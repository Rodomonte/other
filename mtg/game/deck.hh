// DECK

#ifndef deck_hh
#define deck_hh

#include "card.hh"


struct Deck {
  int       id;
  Format    format;
  str       name;
  vec<Card> main, side, extra;

  Deck(int _id, Format _format): id(_id), format(_format) {}
  Deck(vec<Card> _main, vec<Card> _side, vec<Card> _extra):
    main(_main), side(_side), extra(_extra) {}

  //str file(){ return str(sprintf(_, "%s/d%4d.deck", DECK_DIRS[format], id)); }

  void from_str(str& s){

  }

  void from_file(){
    str s;

  }

  // str string(){
  //   int i;
  //   map<string, int> m;
  //   map<string, int>::iterator it;

  //   for(i = 0; i < main.size(); ++i){
  //     if((it = m.find(main[i].name)) == m.end())
  //       m[main[i].name] = 1;
  //     else ++it->second;
  //   }

  //   printf("%s:\n", name.c_str());
  //   for(i = 0; i < main.size(); ++i)
  //     printf("%dx %s\n", m[main[i].name], main[i].string().c_str());
  // }

  // void to_file(){
  //   FILE* fp;
  //   fp = fopen(file().c_str(), "w");
  //   //fprintf(
  // }
};


#endif
