// SIM

#ifndef sim_h
#define sim_h

//#include "game.h"
#include "select.h"


struct Sim {
  Sim(){}

  int init(){
    int opt;
    Format format;
    vec<Bot> bots;
    vd decks;

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

  int play(vd& decks){
    check(init());
    check(game.run());
    return 0;
  }

  int sim(vd& decks){

    return 0;
  }
};


#endif
