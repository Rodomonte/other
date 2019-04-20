// POKER

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

#define gc getchar_unlocked
#define pb push_back
#define SN 4
#define RN 13
#define HN 5


const char RANK[RN] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'},
           SUIT[SN] = {'C','D','S','H'};
const int CN = RN * SN;
int RI[85], SI[86];


bool isrank(char c){
  int i;
  for(i = 0; i < RN; ++i)
    if(c == RANK[i]) return true;
  return false;
}

bool issuit(char c){
  int i;
  for(i = 0; i < SN; ++i)
    if(c == SUIT[i]) return true;
  return false;
}


struct card {
  char r,s;
  card(){}
  card(char r0, char s0): r(r0), s(s0) {}
  card& operator=(card o){ r = o.r, s = o.s; }
  bool operator==(card o){ return r == o.r && s == o.s; }
  bool operator<(card o){ return RI[r] < RI[o.r]; }
  string str(){ return string("") + r + s; }
};

const card C2('2','C'), C3('3','C'), C4('4','C'), C5('5','C'), C6('6','C'),
           C7('7','C'), C8('8','C'), C9('9','C'), CT('T','C'), CJ('J','C'),
           CQ('Q','C'), CK('K','C'), CA('A','C'),
           D2('2','D'), D3('3','D'), D4('4','D'), D5('5','D'), D6('6','D'),
           D7('7','D'), D8('8','D'), D9('9','D'), DT('T','D'), DJ('J','D'),
           DQ('Q','D'), DK('K','D'), DA('A','D'),
           S2('2','S'), S3('3','S'), S4('4','S'), S5('5','S'), S6('6','S'),
           S7('7','S'), S8('8','S'), S9('9','S'), ST('T','S'), SJ('J','S'),
           SQ('Q','S'), SK('K','S'), SA('A','S'),
           H2('2','H'), H3('3','H'), H4('4','H'), H5('5','H'), H6('6','H'),
           H7('7','H'), H8('8','H'), H9('9','H'), HT('T','H'), HJ('J','H'),
           HQ('Q','H'), HK('K','H'), HA('A','H');


struct deck {
  vector<card> d;
  void shuf(){
    int i,j;
    card t;
    for(i = d.size()-1; i > 0; --i)
      j = rand()%(i+1), t = d[i], d[i] = d[j], d[j] = t;
  }
} DECK ;


struct hand {
  vector<card> h;
  hand(){}
  hand(vector<card> h0): h(h0) {}

  // card top(){
  //   int i,j,m;
  //   for(i = 0, m = -1; i < HN; ++i)
  //     if(RI[h[i].r] > m) m = RI[h[i].r], j = i;
  //   return j;
  // }

  bool has(char n){
    int i;
    for(i = 0; i < HN; ++i)
      if((isrank(n) && h[i].r == n) || (issuit(n) && h[i].s == n)) return true;
    return false;
  }

  // bool operator==(hand& o) const {
  //   if(rf() && o.rf()) return true;
  //   if(sf() && o.sf() && h[top()].r == o.h[o.top()].r) return true;
  //   if(kind(4) && o.kind(4) &&
  //   return false;
  // }

  // bool operator<(hand& o) const {
  //   if(rf()){
  //     if(o.rf
  //   }
  //   return true;
  // }
};


// Result
struct R { int n,w,t; R(){} R(int n0, int w0, int t0): n(n0), w(w0), t(t0) {} };

struct TexasHoldEm {
  /*
   - With starting hand XY, what % chance of winning with P players?
     e.g. AA > 50% with 2P, probably < 50% with more P
   - With suited starting hand, what % chance of flush?
   - What % of my cash is worth betting to see 2p/3k on flop w/ nothing?
  */

  map<string,R> m;

  // w=-1: lose, w=0: tie, w=1: win
  void ins(card a, card b, char w){
    string k = "";
    map<string,R>::iterator it;
    k += (a.r < b.r) ? a.r : b.r, k += (a.r < b.r) ? b.r : a.r;
    if(a.s == b.s) k += 'S';
    it = m.find(k);
    if(it == m.end()) m[k] = R(1, (w == 1) ? 1 : 0, w ? 0 : 1);
    else{
      ++it->second.n;
      if(w == 1) ++it->second.w;
      if(!w) ++it->second.t;
    }
  }
} the ;


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
  bool kind(int n, char r){
    int j,k;
    for(j = k = 0; j < HN; ++j)
      if(h[j].r == r || h[j].r == '2') ++k;
    return k == n;
  }

  bool st(){
    char f;
    int i,j, n;
    for(n = i = 0; i < HN; ++i)
      if(h[i].r == '2') ++n;
    for(i = 0; i != RN-3; ++i){
      for(j = i, f = 1; j != ((i == RN-4) ? 1 : i+5);
          j = (j == RN-1) ? 0 : j+1){
        if(RANK[j] != '2' && has(RANK[j])) continue;
        else if(n > 0) --n;
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
      if(RANK[i] != '2') ++j;
    return (j == 2);
  }

  bool sf(){ return st() && fl(); }

  bool rf(){
    if(!st() || !fl()) return false;
    int i,d,n;
    for(i = 0; i < HN; ++i){
      if(h[i].r == '2') ++d;
      if(h[i].r == 'A' || h[i].r == 'K' || h[i].r == 'Q' || h[i].r == 'J' ||
         h[i].r == 'T') ++n;
    }
    return (d + n == 5);
  };
};

struct DeucesWild {
  int pay(dwhand h){
    if(h.rf() && !h.has('2')) return 250;
    if(h.kind(4, 2)) return 200;
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
    char c;
    int i, m,n,t, a[32];
    dwhand h,hn;
    deck d;
    map<double, int> r;
    map<double, int>::reverse_iterator rt;

    const int HOLDS = 5;

    for(m = 0; m < (1 << HOLDS); ++m)
      a[m] = 0;
    d = DECK, d.shuf(), n = 0;
    for(i = 0; i < HN; ++i)
      h.h.pb(d.d.back()), d.d.pop_back();

    while(++n < 10000){
      for(m = 0; m < (1 << HOLDS); ++m){
        hn = h, d.shuf();
        for(t = i = 0; i < HN; ++i)
          if(!(m & (1 << i))) hn.h.erase(hn.h.begin()+i-t), ++t;
        for(i = 0; i < t; ++i)
          hn.h.pb(d.d[i]);
        a[m] += pay(hn);
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
} dw ;


void init(){
  int i,j;
  srand(time(0));
  for(i = 0; i < RN; ++i) RI[RANK[i]] = i;
  for(i = 0; i < SN; ++i) SI[SUIT[i]] = i;
  for(i = 0; i < RN; ++i) for(j = 0; j < SN; ++j)
    DECK.d.pb(card(RANK[i], SUIT[j]));
}

int main(){
  init();
  while(1)
    dw.rand(), printf("\n!!!!!!!!\n"), gc();
  return 0;
}
