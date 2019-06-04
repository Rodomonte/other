// BOT

#ifndef bot_hh
#define bot_hh

#include "game.hh"


struct Bot {
  int seat;

  Bot(int _seat): seat(_seat) {}

  virtual stat main1(Game& g) = 0;
  virtual stat attack(Game& g) = 0;
  virtual stat block(Game& g) = 0;
  virtual stat main2(Game& g) = 0;
  virtual stat respond(Game& g, Card& c) = 0;
};


#endif
