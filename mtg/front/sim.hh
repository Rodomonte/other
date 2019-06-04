// SIM

#ifndef sim_hh
#define sim_hh

#include "../game/human.hh"
#include "create.hh"


struct Sim {
  Game g;

  Sim(){}

  stat init(){
    int       opt;
    Format    format;
    vec<Bot*>  bots;
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

    bots.pb(new Human(0));
    bots.pb(new Human(1));

    g = Game(format, bots, decks);

    return PASS;
  }

  stat play(){
    check(init());
    check(g.run());
    //! log game
    delete g.bot[0];
    delete g.bot[1];
    return PASS;
  }

  stat sim(){

    return PASS;
  }
};


#endif
