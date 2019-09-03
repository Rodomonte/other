// POKER UTIL


#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

#define str std::string
#define vec std::vector
#define map std::map
#define gc getchar_unlocked
#define pb push_back
#define SN 4
#define RN 13


bool DBG = false;
const char RANK[RN] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'},
           SUIT[SN] = {'C','D','S','H'};
const int CN = RN * SN;
int RI[85], SI[86];


int min(int a, int b){ return (a < b) ? a : b; }
int max(int a, int b){ return (a > b) ? a : b; }

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
  bool operator==(card o){ return r == o.r && s == o.s; }
  bool operator<(card o){ return RI[r] < RI[o.r]; }
  str string(){ return str("") + r + s; }
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
  vec<card> d;

  card draw(){
    card c(d.back());
    d.pop_back();
    return c;
  }

  void erase(card c){
    vec<card>::iterator it;
    for(it = d.begin(); it != d.end(); ++it)
      if(*it == c){ d.erase(it); break; }
  }

  void shuf(){
    int i,j;
    card t;
    for(i = d.size()-1; i > 0; --i)
      j = rand()%(i+1), t = d[i], d[i] = d[j], d[j] = t;
  }
} DECK ;


struct hand {
  vec<card> h;
  hand(){}
  hand(vec<card> _h): h(_h) {}

  void pb(card c){ h.pb(c); }
  card popb(){ card c(h.back()); h.pop_back(); return c; }
  int size(){ return h.size(); }
  bool empty(){ return !size(); }
  void clear(){ h.clear(); }
  card& back(){ return h.back(); }
  card& operator[](int i){ return h[i]; }

  virtual str string(){
    int i;
    str r = "";
    for(i = 0; i < size()-1; ++i)
      r += h[i].string(), r += " ";
    r += h[size()-1].string();
    return r;
  }

  bool has(char n){
    int i;
    for(i = 0; i < size(); ++i)
      if((isrank(n) && h[i].r == n) || (issuit(n) && h[i].s == n)) return true;
    return false;
  }

  struct {
    bool operator()(card a, card b) const {
      return RI[a.r] > RI[b.r];
    }
  } cardcmp;
  void sort(){
    std::sort(h.begin(), h.end(), cardcmp);
  }
};


struct pot {
  int cash;
  vec<int> players;
  pot(): cash(0) {}
  bool operator==(pot& o){
    int i;
    if(players.size() != o.players.size()) return false;
    std::sort(players.begin(), players.end());
    std::sort(o.players.begin(), o.players.end());
    for(i = 0; i < players.size(); ++i)
      if(players[i] != o.players[i]) return false;
    return true;
  }
};


void init(){
  int i,j;
  srand(time(0));
  for(i = 0; i < RN; ++i) RI[RANK[i]] = i;
  for(i = 0; i < SN; ++i) SI[SUIT[i]] = i;
  for(i = 0; i < RN; ++i) for(j = 0; j < SN; ++j)
    DECK.d.pb(card(RANK[i], SUIT[j]));
}
