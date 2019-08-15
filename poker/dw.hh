// DEUCES WILD

#include "util.hh"

#define HN 5


struct dwhand : hand {
  dwhand(){}

  // EXACTLY n of a kind
  bool kind(int n){
    int i,j,k;
    for(i = 0; i < RN; ++i){
      for(j = k = 0; j < HN; ++j)
        if(h[j].r == RANK[i] || h[j].r == '2') ++k;
      if(k == n) return true;
    }
    return false;
  }

  // bool kind(int n, char r){
  //   int j,k;
  //   for(j = k = 0; j < HN; ++j)
  //     if(h[j].r == r || h[j].r == '2') ++k;
  //   return k == n;
  // }

  bool st(){
    char f;
    int i,j, n,t;
    for(n = i = 0; i < HN; ++i)
      if(h[i].r == '2') ++n;
    for(i = 0; i != RN-3; ++i){
      for(j = i, t = n, f = 1; j != ((i == RN-4) ? 1 : i+5);
          j = (j == RN-1) ? 0 : j+1){
        if(RANK[j] != '2' && has(RANK[j])) continue;
        else if(t > 0) --t;
        else{ f = 0; break; }
      }
      if(f) return true;
    }
    return false;
  }

  bool fl(){
    char f;
    int i,j;
    for(i = 0; i < SN; ++i){
      for(j = 0, f = 1; j < HN; ++j)
        if(h[j].s != SUIT[i] && h[j].r != '2'){ f = 0; break; }
      if(f) return true;
    }
    return false;
  }

  bool fh(){
    int i,j, r[RN]={0};
    for(i = 0; i < HN; ++i)
      ++r[RI[h[i].r]];
    for(i = j = 0; i < RN; ++i)
      if(RANK[i] != '2' && r[i]) ++j;
    return (j == 2);
  }

  bool sf(){ return st() && fl(); }

  bool rf(){
    if(!st() || !fl()) return false;
    int i,d,n;
    for(d = n = i = 0; i < HN; ++i){
      if(h[i].r == '2') ++d;
      if(h[i].r == 'A' || h[i].r == 'K' || h[i].r == 'Q' || h[i].r == 'J' ||
         h[i].r == 'T') ++n;
    }
    return (d + n == 5);
  };
};

struct DeucesWild {
  int HOLDS, a[32];
  dwhand h;
  deck d;
  map<double, int> r;

  int pay(dwhand h){
    if(h.rf() && !h.has('2')) return 250;
    if(h.kind(4, '2')) return 200;
    if(h.rf() && h.has('2')) return 20;
    if(h.kind(5)) return 12;
    if(h.sf()) return 9;
    if(h.kind(4)) return 4;
    if(h.fh()) return 4;
    if(h.fl()) return 3;
    if(h.st()) return 2;
    if(h.kind(3)) return 1;
    return 0;
  }

  void rand(){
    int i, m,n,t;
    dwhand hn;
    map<double, int>::reverse_iterator rt;

    HOLDS = 5;
    for(i = 0; i < (1 << HOLDS); ++i)
      a[i] = 0;
    d = DECK, d.shuf(), h.h.clear();
    for(i = 0; i < HN; ++i)
      h.h.pb(d.d.back()), d.d.pop_back();

    n = 0;
    while(++n < 15000){
      for(m = 0; m < (1 << HOLDS); ++m){
        hn = h, d.shuf();
        for(t = i = 0; i < HN; ++i)
          if(!(m & (1 << i))) hn.h.erase(hn.h.begin()+i-t), ++t;
        for(i = 0; i < t; ++i)
          hn.h.pb(d.d[i]);
        a[m] += (t = pay(hn));
      }

      if(!(n % 100)){
        r.clear();
        for(m = 0; m < (1 << HOLDS); ++m)
          r[(double)a[m] / n] = m;
        printf("\n\n");
        for(i = 0; i < HN; ++i)
          printf("%s ", h.h[i].str().c_str());
        printf(":\n");
        for(rt = r.rbegin(); rt != r.rend(); ++rt){
          printf("%.2lf:", rt->first);
          for(i = 0; i < HN; ++i)
            if(rt->second & (1 << i)) printf(" %s", h.h[i].str().c_str());
          printf("\n");
        }
      }
    }
  }

  void query(){
    int i, n,p,t;
    char b[16];
    card c;
    dwhand hn;

    printf("Hold: ");
    scanf("%s", b);
    d = DECK, d.shuf(), h.h.clear();
    if(b[0]){
      for(i = 0; i < HN*3; i += 3){
        c.r = b[i], c.s = b[i+1];
        h.h.pb(c), d.erase(c);
        if(!b[i+2]) break;
      }
    }

    n = p = 0;
    while(++n < 300000){
      hn = h, d.shuf(), t = HN - hn.h.size();
      for(i = 0; i < t; ++i)
        hn.h.pb(d.d[i]);
      p += pay(hn);

      // if(hn.rf() && !hn.has('2')) printf("Royal Flush\n");
      // if(hn.kind(4, '2')) printf("Four Deuces: %s\n", hn.str().c_str());
      // if(hn.rf() && hn.has('2')) printf("Royal Flush with Deuce\n");
      // if(hn.kind(5)) printf("Five of a Kind\n");
      // if(hn.sf()) printf("Straight Flush\n");
      // if(hn.kind(4)) printf("Four of a Kind\n");
      // if(hn.fh()) printf("Full House");
      // if(hn.fl()) printf("Flush\n");
      // if(hn.st()) printf("Straight\n");
      // if(h.kind(3)) printf("Three of a Kind\n");
    }
    printf("Expected: %.2lf\n", (double)p / n);
  }
} dw ;
