// TEXAS HOLD EM HAND

#include "util.hh"

#define HN 5


struct texhand : hand {
  texhand(){}
  texhand(vec<card> _h): hand(_h) {}

  virtual str string(){
    str r(hand::string());
    if(!rf().empty()) r += " (Royal Flush)";
    else if(!sf().empty()) r += " (Straight Flush)";
    else if(!kind(4).empty()) r += " (Four of a Kind)";
    else if(!fh().empty()) r += " (Full House)";
    else if(!fl().empty()) r += " (Flush)";
    else if(!st().empty()) r += " (Straight)";
    else if(!kind(3).empty()) r += " (Three of a Kind)";
    else if(!pair2().empty()) r += " (Two Pair)";
    else if(!kind(2).empty()) r += " (Pair)";
    return r;
  }

  texhand hi(){
    texhand r(*this);
    r.sort();
    while(r.size() > HN)
      r.popb();
    return r;
  }

  texhand kind(int n){
    bool f;
    int i,j,k;
    texhand r;
    for(i = RN-1; i >= 0; --i){
      for(k = j = 0; j < size(); ++j)
        if(h[j].r == RANK[i]) ++k;
      if(k == n){
        for(j = 0; j < size(); ++j)
          if(h[j].r == RANK[i]) r.pb(h[j]);
        break;
      }
    }
    if(r.empty()) return r;
    sort();
    for(k = i = 0; i < size() && r.size() < HN; ++i){
      for(f = true, j = 0; j < r.size(); ++j)
        if(h[i].r == r[j].r){ f = false; break; }
      if(f) r.pb(h[i]);
    }
    return r;
  }

  texhand pair2(){
    bool f;
    int i,j,k;
    texhand r;
    for(i = RN-1; i >= 0; --i){
      for(j = k = 0; j < size(); ++j)
        if(h[j].r == RANK[i]) ++k;
      if(k == 2)
        for(j = 0; j < size(); ++j)
          if(h[j].r == RANK[i]) r.pb(h[j]);
      if(r.size() == 4) break;
    }
    if(r.size() < 4) return texhand();
    sort();
    for(i = 0; i < size(); ++i){
      for(f = true, j = 0; j < r.size(); ++j)
        if(h[i].r == r[j].r){ f = false; break; }
      if(f){ r.pb(h[i]); break; }
    }
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
    int i,j,k;
    texhand r;
    sort();
    for(i = 0; i < SN; ++i){
      for(k = j = 0; j < size(); ++j)
        if(h[j].s == SUIT[i]) ++k;
      if(k >= HN){
        for(j = 0; j < size() && r.size() < HN; ++j)
          if(h[j].s == SUIT[i]) r.pb(h[j]);
        break;
      }
    }
    return r;
  }

  texhand fh(){
    char a,b;
    int i,j,k;
    texhand r;
    if(kind(2).empty() || kind(3).empty()) return r;
    sort(), a = b = 0;
    for(i = 0; i < RN; ++i){
      for(k = j = 0; j < size(); ++j)
        if(h[j].r == RANK[i]) ++k;
      if((!a && k == 3) || (!b && k == 2))
        for(j = 0; j < size(); ++j)
          if(h[j].r == RANK[i]) r.pb(h[j]);
      if(a && b) break;
    }
    return r;
  }

  texhand sf(){
    int i,j,k;
    texhand r;
    sort();
    for(i = 0; i < SN; ++i){
      for(k = j = 0; j < size(); ++j)
        if(h[j].s == SUIT[i]) ++k;
      if(k >= HN){
        for(j = 0; j < size(); ++j)
          if(h[j].s == SUIT[i]) r.pb(h[j]);
        break;
      }
    }
    return r.st();
  }

  texhand rf(){
    texhand r;
    r = sf();
    return (!r.has('A') || !r.has('K')) ? texhand() : r;
  }

  int cmp(texhand o){
    char c,d;
    int i,j,k,l;
    texhand a,b,p,q;

    a = rf(), b = o.rf();
    if(a.empty() && !b.empty()) return -1;
    if(!a.empty() && b.empty()) return 1;
    if(!a.empty() && !b.empty()) return 0;

    a = sf(), b = o.sf();
    if(a.empty() && !b.empty()) return -1;
    if(!a.empty() && b.empty()) return 1;
    if(!a.empty() && !b.empty()){
      a.sort(), b.sort();
      c = (a[0].r == 'A' && a[1].r == '5') ? a[1].r : a[0].r;
      d = (b[0].r == 'A' && b[1].r == '5') ? a[1].r : a[0].r;
      if(RI[c] < RI[d]) return -1;
      if(RI[c] > RI[d]) return 1;
      return 0;
    }

    a = kind(4), b = o.kind(4);
    if(a.empty() && !b.empty()) return -1;
    if(!a.empty() && b.empty()) return 1;
    if(!a.empty() && !b.empty()){
      for(i = RN-1; i >= 0; --i){
        for(l = k = j = 0; j < HN; ++j){
          if(a[j].r == RANK[i]) ++k;
          if(b[j].r == RANK[i]) ++l;
        }
        if(k < 4 && l == 4) return -1;
        if(k == 4 && l < 4) return 1;
        if(k == 4 && l == 4){
          for(j = 0; j < HN; ++j){
            if(a[j].r != RANK[i]) c = a[j].r;
            if(b[j].r != RANK[i]) d = a[j].r;
          }
          if(RI[c] < RI[d]) return -1;
          if(RI[c] > RI[d]) return 1;
          return 0;
        }
      }
      //unr
    }

    a = fh(), b = o.fh();
    if(a.empty() && !b.empty()) return -1;
    if(!a.empty() && b.empty()) return 1;
    if(!a.empty() && !b.empty()){
      for(i = RN-1; i >= 0; --i){
        for(l = k = j = 0; j < HN; ++j){
          if(a[j].r == RANK[i]) ++k;
          if(b[j].r == RANK[i]) ++l;
        }
        if(k < 3 && l == 3) return -1;
        if(k == 3 && l < 3) return 1;
      }
      for(i = RN-1; i >= 0; --i){
        for(l = k = j = 0; j < HN; ++j){
          if(a[j].r == RANK[i]) ++k;
          if(b[j].r == RANK[i]) ++l;
        }
        if(k < 2 && l == 2) return -1;
        if(k == 2 && l < 2) return 1;
        if(k == 2 && l == 2) return 0;
      }
      //unr
    }

    a = fl(), b = o.fl();
    if(a.empty() && !b.empty()) return -1;
    if(!a.empty() && b.empty()) return 1;
    if(!a.empty() && !b.empty()){
      a.sort(), b.sort();
      for(i = 0; i < HN; ++i){
        if(RI[a[i].r] < RI[b[i].r]) return -1;
        if(RI[a[i].r] > RI[b[i].r]) return 1;
      }
      return 0;
    }

    a = st(), b = o.st();
    if(a.empty() && !b.empty()) return -1;
    if(!a.empty() && b.empty()) return 1;
    if(!a.empty() && !b.empty()){
      a.sort(), b.sort();
      c = (a[0].r == 'A' && a[1].r == '5') ? a[1].r : a[0].r;
      d = (b[0].r == 'A' && b[1].r == '5') ? a[1].r : a[0].r;
      if(RI[c] < RI[d]) return -1;
      if(RI[c] > RI[d]) return 1;
      return 0;
    }

    a = kind(3), b = o.kind(3);
    if(a.empty() && !b.empty()) return -1;
    if(!a.empty() && b.empty()) return 1;
    if(!a.empty() && !b.empty()){
      for(i = RN-1; i >= 0; --i){
        for(l = k = j = 0; j < HN; ++j){
          if(a[j].r == RANK[i]) ++k;
          if(b[j].r == RANK[i]) ++l;
        }
        if(k < 3 && l == 3) return -1;
        if(k == 3 && l < 3) return 1;
        if(k == 3 && l == 3){
          p.clear(), q.clear();
          for(j = 0; j < HN; ++j){
            if(a[j].r != RANK[i]) p.pb(a[j]);
            if(b[j].r != RANK[i]) q.pb(b[j]);
          }
          p.sort(), q.sort();
          for(j = 0; j < 2; ++j){
            if(RI[p[j].r] < RI[q[j].r]) return -1;
            if(RI[p[j].r] > RI[q[j].r]) return 1;
          }
          return 0;
        }
      }
      //unr
    }

    a = pair2(), b = o.pair2();
    if(a.empty() && !b.empty()) return -1;
    if(!a.empty() && b.empty()) return 1;
    if(!a.empty() && !b.empty()){
      p.clear(), q.clear();
      for(i = RN-1; i >= 0; --i){
        for(l = k = j = 0; j < HN; ++j){
          if(a[j].r == RANK[i]) ++k;
          if(b[j].r == RANK[i]) ++l;
        }
        for(j = 0; j < HN; ++j){
          if(k == 2 && p.size() < 4 && a[j].r == RANK[i]) p.pb(a[j]);
          if(l == 2 && q.size() < 4 && b[j].r == RANK[i]) q.pb(b[j]);
        }
      }
      p.sort(), q.sort();
      for(j = 0; j < 4; ++j){
        if(RI[p[j].r] < RI[q[j].r]) return -1;
        if(RI[p[j].r] > RI[q[j].r]) return 1;
      }
      for(j = 0; j < HN; ++j){
        if(!p.has(a[j].r)) c = a[j].r;
        if(!q.has(b[j].r)) d = b[j].r;
      }
      if(RI[c] < RI[d]) return -1;
      if(RI[c] > RI[d]) return 1;
      return 0;
    }

    a = kind(2), b = o.kind(2);
    if(a.empty() && !b.empty()) return -1;
    if(!a.empty() && b.empty()) return 1;
    if(!a.empty() && !b.empty()){
      for(i = RN-1; i >= 0; --i){
        for(l = k = j = 0; j < HN; ++j){
          if(a[j].r == RANK[i]) ++k;
          if(b[j].r == RANK[i]) ++l;
        }
        if(k < 2 && l == 2) return -1;
        if(k == 2 && l < 2) return 1;
        if(k == 2 && l == 2){
          p.clear(), q.clear();
          for(j = 0; j < HN; ++j){
            if(a[j].r != RANK[i]) p.pb(a[j]);
            if(b[j].r != RANK[i]) q.pb(b[j]);
          }
          p.sort(), q.sort();
          for(j = 0; j < 3; ++j){
            if(RI[p[j].r] < RI[q[j].r]) return -1;
            if(RI[p[j].r] > RI[q[j].r]) return 1;
          }
          return 0;
        }
      }
      //unr
    }

    a = hi(), b = o.hi();
    a.sort(), b.sort();
    for(j = 0; j < HN; ++j){
      if(RI[a[j].r] < RI[b[j].r]) return -1;
      if(RI[a[j].r] > RI[b[j].r]) return 1;
    }
    return 0;
  }
};
