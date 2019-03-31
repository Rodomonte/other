// POKER

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

#define pb push_back
#define SN 4
#define RN 13
#define HN 5
#define LHN 3


const char RANK[RN] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'},
           SUIT[SN] = {'C','D','S','H'};
const int CN = RN * SN;
int RI[85], SI[86];


struct card {
  char r,s;
  card(){}
  card(char r0, char s0): r(r0), s(s0) {}
  bool operator==(card o) const { return r == o.r && s == o.s; }
  bool operator<(card o) const { return RI[r] < RI[o.r]; }
};
vector<card> DECK;

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

void shuf(vector<card>& d){
  int i,j;
  card t;
  for(i = CN-1; i > 0; --i)
    j = rand()%(i+1), t = d[i], d[i] = d[j], d[j] = t;
}


struct Hand {
  card c[HN];
  Hand(card c0[HN]){ int i; for(i = 0; i < HN; ++i) c[i] = c0[i]; };

  card top(){
    int i,j,m;
    for(i = 0, m = -1; i < HN; ++i)
      if(RI[c[i].r] > m) m = RI[c[i].r], j = i;
    return j;
  }

  bool has(char n){
    int i;
    for(i = 0; i < HN; ++i)
      if((isrank(n) && c[i].r == n) || (issuit(n) && c[i].s == n)) return true;
    return false;
  }

  // EXACTLY n of a kind
  bool kind(int n){
    int i,j,k;
    for(i = 0; i < RN; ++i){
      for(j = k = 0; j < HN; ++j)
        if(c[j].r == RANK[i]) ++k;
      if(k == n) return true;
    }
    return false;
  }
  bool kind(int n, char r){
    int j,k;
    for(j = k = 0; j < HN; ++j)
      if(c[j].r == r) ++k;
    return k == n;
  }

  bool twop(){
    char f,r;
    int i,j,k;
    for(i = f = 0; i < RN; ++i){
      for(j = k = 0; j < HN; ++j)
        if(c[j].r == RANK[i]) ++k;
      if(k == 2){ f = 1, r = RANK[i]; break; }
    }
    if(!f) return false;
    for(i = f = 0; i < RN; ++i){
      if(RANK[i] == r) continue;
      for(j = k = 0; j < HN; ++j)
        if(c[j].r == RANK[i]) ++k;
      if(k == 2){ f = 1; break; }
    }
    return f;
  }

  bool st(){
    char f;
    int i,j;
    for(i = RN-1; i != RN-4; i = (i == RN-1) ? 0 : i+1){
      for(j = i, f = 1; j != ((i == RN-1) ? 4 : i+5); j = (j == RN-1) ? 0 : j+1)
        if(!has(RANK[j])){ f = 0; break; }
      if(f) return true;
    }
    return false;
  }

  bool fl(){
    char f;
    int i,j;
    for(i = 0; i < SN; ++i){
      for(j = 0, f = 1; j < HN; ++j)
        if(c[j].s != SUIT[i]){ f = 0; break; }
      if(f) return true;
    }
    return false;
  }

  bool fh(){ return kind(2) && kind(3); }
  bool sf(){ return st() && fl(); }
  bool rf(){ return st() && fl() && has('A') && has('K'); };

  bool operator==(Hand& o) const {
    if(rf() && o.rf()) return true;
    if(sf() && o.sf() && c[top()].r == o.c[o.top()].r) return true;
    if(kind(4) && o.kind(4) &&
    return false;
  }

  bool operator<(Hand& o) const {
    if(rf()){
      if(o.rf
    }
    return _;
  }
};


// Result
struct R { int n,w,t; R(){} R(int n0, int w0, int t0): n(n0), w(w0), t(t0) {} };

// Texas Hold Em
struct THE {
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

  // 2 <= p(#players) <= 10
  void best2(int p){
    int i,j, n;
    card h[10][2], b[5];
    vector<card> d;

    for(n = 1; 1; ++n){
      d = DECK, shuf(d);
      for(i = j = 0; i < 5; ++i) b[i] = d[j++];
      for(i = 0; i < p; ++i) h[i][0] = d[j++], h[i][1] = d[j++];

    }
  }
} the ;


void init(){
  int i,j;
  for(i = 0; i < RN; ++i) RI[RANK[i]] = i;
  for(i = 0; i < SN; ++i) SI[SUIT[i]] = i;
  for(i = 0; i < RN; ++i) for(j = 0; j < SN; ++j)
    DECK.pb(card(RANK[i], SUIT[j]));
}

int main(){
  init();
  the.best2(2);
  return 0;
}
