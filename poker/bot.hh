// POKER BOTS

#include "texhand.hh"


struct tex;

struct bot {
  bool out;
  int cash, bet, score, id;
  texhand hand;
  bot(int c): cash(c), bet(0), score(0), out(false) {}
  void pay(int c){
    if(c > cash) c = cash, out = true;
    cash -= c, bet += c;
  }
  virtual str string() = 0;
  virtual int bet_tex(tex* g) = 0; // return -1 to fold
};

struct human : bot {
  human(int c): bot(c) {}
  int bet_tex(tex* g);
  str string(){ return str("Player"); }
};

struct ai : bot {
  int DIV;
  float MAX, SCALE;
  ai(int c): bot(c) {}
  int bet_tex(tex* g);
  str string(){
    char buf[64];
    sprintf(buf, "Bot %d (DIV=%d MAX=%.2f SCALE=%.2f)", id, DIV, MAX, SCALE);
    return str(buf);
  }
};

bot* genbot(int id){
  ai* b = new ai(1000);
  b->id = id;
  b->DIV = rand()%10+1; // 1-10
  b->MAX = (float)(rand()%81+20)/100.0f; // 20-100%
  b->SCALE = (float)(rand()%81+20)/100.0f; // 20-100%
  return b;
}
