// CARD

#ifndef card_hh
#define card_hh

#include "../core/util.hh"


struct Game;

struct Card {
  int             id, bpow, btuf;
  str             name;
  uset<str>       types, quals;
  umap<Cost, int> cost;
  umap<str, int>  counters;

  Card(str& _name, int _pow, int _tuf, uset<str>& _types, uset<str>& _quals,
       umap<Cost, int>& _cost): name(name), pow(_pow), tuf(_tuf),
       types(_types), quals(_quals), cost(_cost) {}

  str string(){
    int i;
    umap<Cost, int>::iterator it;
    sprintf(buf, "%s (", name.c_str());
    for(i = 0; buf[i] != '('; ++i);
    //! for(it = COSTS
    return str(buf);
  }

  int cmc(){ return mw + mu + mk + mr + mg + mc + ma; }

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
    return in(ART, types) || in(CRE, types) || in(ENC, types) || in(LAN, types);
  }
  bool nlperm(){ return perm() && !in(LAN, types); }

  stat load(int id){
    return PASS;
  }

  stat write(){
    return PASS;
  }
};


#endif
