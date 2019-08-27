// POKER BOTS

#include "texhand.hh"


struct tex;

struct bot {
  bool out;
  int cash, bet;
  texhand hand;
  bot(int c): cash(c), bet(0), out(false) {}
  void pay(int c){ cash -= c, bet += c; }
  virtual int bet_tex(tex* g) = 0; // return -1 to fold
};


struct human : bot {
  human(int c): bot(c) {}
  int bet_tex(tex* g);
};


struct ai : bot {
  ai(int c): bot(c) {}
  int bet_tex(tex* g);
};
