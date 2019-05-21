// MAIN

#include "create.hh"
#include "sim.hh"
#include "update.hh"
#include "view.hh"


int main(){
  int opt;

  while(1){
    opt = -1;
    while(opt < 0 || opt > 4){
      printf("%s", MAIN_OPTS.c_str());
      try{ scanf("%d", &opt); }catch(...){}
    }

    switch(opt){
      case 0: check(KILL);              break;
      case 1: check(update_lib(lib));   break;
      case 2: check(view_lib(lib));     break;
      case 3: check(view_decks(decks)); break;
      case 4: check(create_card());     break;
      case 5: check(create_deck(lib));  break;
      case 6: check(Sim().play(decks)); break;
      case 7: check(Sim().sim(decks));  break;
    }

  }
  return 0;
}
