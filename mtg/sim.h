// SIM

#ifndef sim_h
#define sim_h

#include "log.h"

struct Sim {

  void init(){
    int o;
    o = 0;
    while(o < 0 || o > 3){
      printf("(0) Exit\n"
             "(1) Back\n"
             "(2) EDH\n"
             "(3) Modern\n"
             "  >");

      if(o == 0 || o == 1) return o;
      else if(o == 2 || o == 3){
        //!

      }
    }

  }

  int run(){
    int r;
    r = init();
    if(r == 0 || r == 1) return r;

    return r;
  }
};

#endif
