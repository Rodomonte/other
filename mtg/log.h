// LOG

#ifndef log_h
#define log_h

#include "game.h"

struct Log {
  vec<Game> g;

  Log(){}
  Log(Game& _g): g({_g}) {}

  void save(){
    //! Pickle

  }

  int run(){

    return 2;
  }
};

#endif
