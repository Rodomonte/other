// CARD

#ifndef card_h
#define card_h

#include "util.h"

struct Card {
  int       mwhi, mblu, mblk, mred, mgre, mcol, mgen, pow, tuf, tpow, ttuf;
  string    name;
  vs        types, quals;
  vec<Qual> q;

  Card(string _name, int _mwhi, int _mblu, int _mblk, int _mred, int _mgre
     , int _mcol, int _mgen, int _pow, int _tuf, vs _types, vs _quals):
    name(name), mwhi(_mwhi), mblu(_mblu), mblk(_mblk), mred(_mred)
  , mgre(_mgre), mcol(_mcol), mgen(_mgen), pow(_pow), tuf(_tuf), tpow(_pow)
  , ttuf(_tuf), types(_types), quals(_quals) {}

  int cmc(){ return mwhi + mblu + mblk + mred + mgre + mcol + mgen; }

  bool is_perm(){
    return in("Artifact", types) || in("Creature", types)
        || in("Enchantment", types) || in("Land", types);
  }
  bool is_nlperm(){ return is_perm() && !in("Land", types); }
};

#endif
