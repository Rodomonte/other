// TEXAS HOLD EM

#include "util.hh"

#define HN 5


struct texhand : hand {
  texhand(){}
  texhand(vec<card> _h): hand(_h) {}

  texhand hi(){
    texhand r(*this);
    r.sort();
    while(r.size() > HN)
      r.popb();
    return r;
  }

  //! Also return highest 3
  texhand kind(int n){
    int i,j,k;
    texhand r;
    for(i = RN-1; i >= 0; --i){
      for(j = k = 0; j < size(); ++j)
        if(h[j].r == RANK[i]) ++k;
      if(k == n){
        for(j = 0; j < size(); ++j)
          if(h[j].r == RANK[i]) r.pb(h[j]);
        break;
      }
    }
    return r;
  }

  //! Also return highest
  texhand pair2(){
    int i,j,k;
    texhand r;
    for(i = RN-1; i >= 0; --i){
      for(j = k = 0; j < size(); ++j)
        if(h[j].r == RANK[i]) ++k;
      if(k == 2){
        for(j = 0; j < size(); ++j)
          if(h[j].r == RANK[i]) r.pb(h[j]);
        if(r.size() == 4) return r;
      }
    }
    if(r.size() == 2) r.clear();
    return r;
  }

  texhand st(){
    bool f;
    int i,j,k;
    texhand r;
    sort();
    for(i = RN-1; i >= HN-2; --i){
      f = true;
      for(j = i; j != ((i-HN < 0) ? i-HN+RN : i-HN); j = (j ? j-1 : RN-1))
        if(!has(RANK[j])){ f = false; break; }
      if(f){
        for(j = i; j != ((i-HN < 0) ? i-HN+RN : i-HN); j = (j ? j-1 : RN-1))
          for(k = 0; k < size(); ++k)
            if(h[k].r == RANK[j]){ r.pb(h[k]); break; }
        return r;
      }
    }
    return r;
  }

  texhand fl(){
    texhand r;

    return r;
  }

  texhand fh(){
    texhand r;

    return r;
  }

  texhand sf(){
    texhand r;

    return r;
  }

  texhand rf(){
    texhand r;

    return r;
  }

  int _cmp(texhand o){
    if(empty() && !o.empty()) return -1;
    if(empty() && o.empty()) return 0;
    if(!empty() && o.empty()) return 1;
    int i;
    sort(), o.sort();
    for(i = 0; i < HN; ++i){
      if(RI[(*this)[i].r] < RI[o[i].r]) return -1;
      if(RI[(*this)[i].r] > RI[o[i].r]) return 1;
    }
    return 0;
  }

  // Full house compares its 3-kind first
  int _cmpfh(texhand o){
    int n;
    if(a.empty() && !b.empty()) return -1;
    if(!a.empty() && b.empty()) return 1;
    n = a.kind(3).cmp(b.kind(3));
    if(n != 0) return n;
    return a.kind(2).cmp(b.kind(2));
  }

  int cmp(texhand o){
    texhand a,b;

    a = rf(), b = o.rf();
    if(!a.empty() || !b.empty()) return a._cmp(b);

    a = sf(), b = o.sf();
    if(!a.empty() || !b.empty()) return a._cmpst(b);

    a = kind(4), b = o.kind(4);
    if(!a.empty() || !b.empty()) return a._cmp(b);

    a = fh(), b = o.fh();
    if(!a.empty() || !b.empty()) return a._cmpfh(b);

    a = fl(), b = o.fl();
    if(!a.empty() || !b.empty()) return a._cmp(b);

    a = st(), b = o.st();
    if(!a.empty() || !b.empty()) return a._cmpst(b);

    a = kind(3), b = o.kind(3);
    if(!a.empty() || !b.empty()) return a._cmp(b);

    a = pair2(), b = o.pair2();
    if(!a.empty() || !b.empty()) return a._cmp(b);

    a = kind(2), b = o.kind(2);
    if(!a.empty() || !b.empty()) return a._cmp(b);

    a = hi(), b = o.hi();
    return a._cmp(b);
  }
};

struct tex {
  // Given a 2-card hand, 0-5 card board, and number of players:
  // % chance of winning
  // % chance of getting certain hand
  // Bet recommendations
  void sim(texhand h, texhand b, int p){
    int i,j,k,m,n,w,t, iter;
    texhand hn,bn;
    deck d,d0;
    vec<texhand> ph;

    d0 = DECK;
    for(i = 0; i < h.size(); ++i)
      d0.erase(h[i]);
    for(i = 0; i < b.size(); ++i)
      d0.erase(b[i]);

    printf("%d\n", ph.size());

    iter = 1000000, w = t = 0;
    for(k = 0; k < iter; ++k){
      d = d0, d.shuf();
      ph.clear(), ph.pb(h);
      for(i = 0; i < p-1; ++i)
        hn.clear(), hn.pb(d.draw()), hn.pb(d.draw()), ph.pb(hn);
      bn = b;
      for(i = 0; i < HN-b.size(); ++i)
        bn.pb(d.draw());

      for(i = 0; i < p; ++i)
        for(j = 0; j < HN; ++j)
          ph[i].pb(bn[j]);
      m = 1;
      for(i = 1; i < p; ++i){
        n = ph[0].cmp(ph[i]);
        if(n < m) m = n;
        if(m == -1) break;
      }
      if(m == 1) ++w;
      if(m == 0) ++t;
    }

    printf("%.2lf%% win\n", (double)w / iter);
    printf("%.2lf%% tie\n", (double)t / iter);
  }
};
