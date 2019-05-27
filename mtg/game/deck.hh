// DECK

#ifndef deck_hh
#define deck_hh

#include "card.hh"


struct Deck {
  int       id;
  Format    format;
  str       name;
  vec<Card> main, side, extra;

  Deck(){}
  Deck(int _id, Format _format): id(_id), format(_format) {}
  Deck(vec<Card> _main, vec<Card> _side, vec<Card> _extra):
    main(_main), side(_side), extra(_extra) {}

  void shuffle(){
    int i,j;
    Card c;
    for(i = main.size()-1; i > 0; --i)
      j = rand()%(i+1), c = main[i], main[i] = main[j], main[j] = c;
  }

  //str file(){ return str(sprintf(_, "%s/d%4d.deck", DECK_DIRS[format], id)); }

  void from_file(){
    str s;

  }

  str string(){
    int i;
    str s;
    umap<str, int> m;
    umap<str, int>::iterator it;

    for(i = 0; i < main.size(); ++i){
      if((it = m.find(main[i].name)) == m.end())
        m[main[i].name] = 1;
      else ++it->second;
    }

    s += name + str(":\n");
    for(it = m.begin(); it != m.end(); ++it)
      s += str("x") + std::to_string(it->second) + str(" ") + it->first +
           str("\n");
    return s;
  }

  // void to_file(){
  //   FILE* fp;
  //   fp = fopen(file().c_str(), "w");
  //   //fprintf(
  // }
};

vec<Deck> deck_lib;


#endif
