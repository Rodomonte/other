// SIM

#ifndef sim_hh
#define sim_hh

#include "../game/game.hh"
#include "select.hh"


struct Sim {
  Game game;

  Sim(){}

  stat init(){
    int       opt;
    Format    format;
    vec<Bot>  bots;
    vec<Deck> decks;

    opt = -1;
    while(opt < 0 || opt > 3){
      printf("(0) Exit\n"
             "(1) Back\n"
             "(2) EDH\n"
             "(3) Modern\n"
             "  >");
      try{ scanf("%d", &opt); }catch(...){}
    }
    if(!opt) kill();
    if(opt == 1) return BACK;

    format = (opt == 2) ? EDH : MOD;
    check(select_decks(format, decks));
    check(select_bots(bots));
    game = Game(format, bots, decks);
    return PASS;
  }

  stat play(){
    check(init());
    check(game.run());
    return PASS;
  }

  stat sim(){

    return PASS;
  }
};


#endif
