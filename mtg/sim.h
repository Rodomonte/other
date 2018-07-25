// SIM

#ifndef sim_h
#define sim_h

#include "log.h"

struct Sim {
  Game g;
  Log  log;

  Sim(){}

  int get_decks(Format format, vec<Deck>& r){
    int i,n,o;
    vec<Deck>& decks = (format == EDH) ? edh : modern;

    while(1){
      o = -1;
      while(o < 0 || o > decks.size()+2){
        printf("(0)   Exit\n"
               "(1)   Back\n"
               "(2)   Ready\n"
               "(3 #) View\n");
        for(i = 0; i < decks.size(); ++i)
          printf("(%d)   %s\n", i+4, decks[i].name.c_str());
        printf("    > ");
        try{ scanf("%d", &o); }catch(...){}
        if(o == 3)
          try{ scanf("%d", &n); n -= 4; }catch(...){}
      }


      if(o == 0 || o == 1) return o;
      else if(o == 2){
        if(r.empty()){ printf("\nNo decks selected!\n\n"); continue; }
        if(r.size() == 1){ printf("\nOnly one deck selected!\n\n"); continue; }
        break;

      }else if(o == 3){
        printf("\n%s:\n\n");
        for(i = 0; i < decks[n].main.size(); ++i){
          decks[n].main[i].print();
          printf("\n");
        }
        printf("\n");

      }else r.pb(decks[n]);
    }
    return 2;
  }

  int get_bots(vec<Bot>& r){

  }

  int init(){
    int o,r;
    o = -1;
    while(o < 0 || o > 3){
      printf("(0) Exit\n"
             "(1) Back\n"
             "(2) EDH\n"
             "(3) Modern\n"
             "  >");
      try{ scanf("%d", &o); }catch(...){}
    }

    if(o == 0 || o == 1) return o;
    else if(o == 2 || o == 3){
      r = get_decks((o == 2) ? EDH : MODERN, decks);
      if(!r || r == 1) return r;
      r = get_bots(bots);
      if(!r || r == 1) return r;
      g = Game(decks, bots);
      log = Log(g);
    }
    return 2;
  }

  int run(){
    int r;
    r = init();
    if(r == 0 || r == 1) return r;
    r = log.run();
    return r;
  }
};

#endif
