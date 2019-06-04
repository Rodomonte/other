// SIM

#ifndef sim_hh
#define sim_hh

#include "../game/game.hh"
#include "create.hh"


struct Sim {
  Game game;

  Sim(){}

  stat init(){
    int       opt;
    Format    format;
    vec<Bot>  bots;
    vec<Deck> decks;

    // opt = -1;
    // while(opt < 0 || opt > 3){
    //   printf("%s", SIM_OPTS);
    //   try{ scanf("%d", &opt); }catch(...){}
    // }

    // switch(opt){
    //   case 0: return KILL;  break;
    //   case 1: return BACK;  break;
    //   case 2: format = EDH; break;
    //   case 3: format = MOD; break;
    // }

    format = MOD;

    while(deck_lib.size() < 2)
      create_deck();
    decks.pb(deck_lib[0]);
    decks.pb(deck_lib[1]);

    bots.pb(Bot(true, 0));
    bots.pb(Bot(true, 1));

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
