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


struct Human : Bot {
  Human(int _seat): Bot(_seat) {}

  stat main1(Game& g){
    printf("%s\n", g.hand_string(seat).c_str());
    // request play
    //!
    return PASS;
  }

  stat attack(Game& g){
    //!
    return PASS;
  }

  stat block(Game& g){
    //!
    return PASS;
  }

  stat main2(Game& g){
    //!
    return PASS;
  }

  stat respond(Game& g, Card& c){
    //!
    return PASS;
  }
};


#endif
