// HUMAN

#ifndef human_hh
#define human_hh

#include "game.hh"


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
