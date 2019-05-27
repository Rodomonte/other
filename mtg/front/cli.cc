// MAIN

#include "create.hh"
#include "sim.hh"
#include "update.hh"
#include "view.hh"


int main(){
  int opt;

  check(parse());

  while(1){
    opt = -1;
    while(opt < 0 || opt > 7){
      printf("\n%s", MAIN_OPTS.c_str());
      try{ scanf("%d", &opt); }catch(...){}
    }

    switch(opt){
      case 0: check(KILL);          break;
      case 1: check(update_lib());  break;
      case 2: check(view_lib());    break;
      case 3: check(view_decks());  break;
      case 4: check(create_card()); break;
      case 5: check(create_deck()); break;
      case 6: check(Sim().play());  break;
      case 7: check(Sim().sim());   break;
    }

  }
  return 0;
}
