// POKER BOTS

#include "util.hh"


struct bot {
  int c;
  hand* h;
  bot(int _c): c(_c) {}
  virtual int bet_tex(hand h, hand b, int p) = 0;
};


struct human : bot {
  human(int _c): bot(c) {}
  int bet_tex(hand h, hand b, int p){

  }
};


struct bot0 : bot {
  bot0(int _c): bot(c) {}
  int bet_tex(hand h, hand b, int p){

  }
};
