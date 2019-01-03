// SIM

#ifndef sim_h
#define sim_h

#include "game.h"


struct Sim {
  Game game;

  Sim(){}

  int pick_decks(Format format, vd& r){
    int i, n, nd, np, op;
    FILE* fp;
    str s;
    vd decks;

    fp = fopen(sprintf("%s/n.txt", DECK_DIRS[format]), "r");
    fscanf(fp, "%d", &nd);
    fclose(fp);
    for(i = 0; i < nd; ++i){
      //!

      fp = fopen(sprintf("%s/d%4d.deck", DECK_DIRS[format], i), "r");
      fseek(fp, 0, SEEK_END);
      n = ftell(fp);
      fseek(fp, 0, SEEK_SET);
      fread(buf, n, 1, fp);
      fclose(fp);
      decks.pb(Deck(str(buf)));
    }
    // = (format == EDH) ? edh : modern;

    while(1){
      op = -1;
      while(op < 0 || op > decks.size()+2){
        printf(SIM_OPS);
        for(i = 0; i < decks.size(); ++i)
          printf("(%d)   %s\n", i+4, decks[i].name.c_str());
        printf("    > ");
        try{ scanf("%d", &op); }catch(...){}
        if(op == 3)
          try{ scanf("%d", &n); n -= 4; }catch(...){}
      }


      check(op);
      if(op == 2){
        if(r.empty()){ printf("\nNo decks selected!\n\n"); continue; }
        if(r.size() == 1){ printf("\nOnly one deck selected!\n\n"); continue; }
        break;

      }else if(op == 3){
        printf("\n%s:\n\n");
        for(i = 0; i < decks[n].main.size(); ++i){
          decks[n].main[i].print();
          printf("\n");
        }
        printf("\n");

      }else r.pb(decks[n]);
    }
    return 0;
  }

  int pick_bots(vec<Bot>& r){

  }

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
