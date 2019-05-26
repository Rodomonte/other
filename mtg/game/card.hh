// CARD

#ifndef card_hh
#define card_hh

#include "../core/util.hh"


struct Game;

struct Card {
  int            bpow, btuf;
  str            name;
  uset<str>      types, quals;
  umap<str, int> cost, counters;

  Card(){}
  Card(str& _name, int _bpow, int _btuf, uset<str>& _types, uset<str>& _quals,
       umap<str, int>& _cost): name(name), bpow(_bpow), btuf(_btuf),
       types(_types), quals(_quals), cost(_cost) {}

  str string(){
    int i;
    uset<str>::iterator jt;
    umap<str, int>::iterator it;

    sprintf(buf, "%s (", name.c_str());
    for(i = 0; buf[i] != '('; ++i);
    for(it = cost.begin(); it != cost.end(); ++it){
      sprintf(buf+i+1, "%d%s ", it->second, it->first.c_str());
      ++i;
      while(buf[i] != ' ') ++i;
    }
    sprintf(buf+i+1, ") "), i += 2;

    if(types.find("Creature") != types.end()){
      sprintf(buf+i+1, "%d/%d ", bpow, btuf);
      ++i;
      while(buf[i] != ' ') ++i;
    }

    for(jt = types.begin(); jt != types.end(); ++jt){
      sprintf(buf+i+1, "%s ", jt->c_str());
      ++i;
      while(buf[i] != ' ') ++i;
    }

    for(jt = QUALS.begin(); jt != QUALS.end(); ++jt)
      if(quals.find(*jt) != quals.end()){
        sprintf(buf+i+1, "- %s -", jt->c_str());
        i += 3;
        while(buf[i] != '-') ++i;
      }
    return str(buf);
  }

  int cmc(){
    int n;
    umap<str, int>::iterator it;
    for(it = cost.begin(), n = 0; it != cost.end(); ++it)
      n += it->second;
    return n;
  }

  int pow(Game& g){
    int n;
    umap<str, int>::iterator it;
    for(it = counters.begin(), n = bpow; it != counters.end(); ++it){
      //!
    }
    return n;
  }

  int tuf(Game& g){
    int n;
    umap<str, int>::iterator it;
    for(it = counters.begin(), n = btuf; it != counters.end(); ++it){
      //!
    }
    return n;
  }

  bool perm(){
    return in(TYPES[ART], types) || in(TYPES[CRE], types) ||
           in(TYPES[ENC], types) || in(TYPES[LAN], types);
  }
  bool nlperm(){ return perm() && !in(TYPES[LAN], types); }

  stat load(int id){
    return PASS;
  }

  stat write(){
    return PASS;
  }
};

umap<str, Card> card_lib;


#endif
