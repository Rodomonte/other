// SIM

#ifndef sim_hh
#define sim_hh

//#include "game.hh"
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

    check(opt);
    format = (opt == 2) ? EDH : MODERN;
    check(pick_decks(format, decks));
    check(pick_bots(bots));
    game = Game(format, bots, decks);
    return 0;
  }

  stat play(vec<Deck>& decks){
    check(init());
    check(game.run());
    return 0;
  }

  stat sim(vec<Deck>& decks){

    return 0;
  }
};


#endif
