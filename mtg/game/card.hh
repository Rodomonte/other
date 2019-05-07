// CARD

#ifndef card_hh
#define card_hh

#include "../core/util.hh"


struct Card {
  int            id, mw, mu, mb, mr, mg, mc, mg, pow, tuf, tpow, ttuf;
  str            name;
  vec<str>       types;
  uset<str>      quals;
  umap<str, int> counters;

  Card(str& _name, int _mw, int _mu, int _mb, int _mr, int _mg, int _mcol
     , int _mg, int _pow, int _tuf, vs& _types, us& _quals):
    name(name), mw(_mw), mu(_mu), mb(_mb), mr(_mr), mg(_mg), mc(_mc), mg(_mg)
  , pow(_pow), tuf(_tuf), tpow(_pow), ttuf(_tuf), types(_types), quals(_quals)
  {}

  int cmc(){ return mwhi + mblu + mblk + mred + mgre + mcol + mgen; }

  bool perm(){
    return in(ART, types) || in(CRE, types) || in(ENC, types) || in(LAN, types);
  }
  bool nlperm(){ return perm() && !in(LAN, types); }

  stat load(int id){

  }

  stat write(){

  }
};


#endif
