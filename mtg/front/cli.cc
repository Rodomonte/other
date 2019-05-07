// MAIN

#include "create.hh"
#include "sim.hh"
#include "update.hh"
#include "view.hh"


int main(){
  int opt;

  load_lib(lib);
  load_decks(decks);

  while(1){
    opt = -1;
    while(opt < 0 || opt > 4){
      printf("%s", MAIN_OPTS);
      try{ scanf("%d", &opt); }catch(...){}
    }

    check((opt == 0) ? KILL
        : (opt == 1) ? update_lib(lib)
        : (opt == 2) ? view_lib(lib)
        : (opt == 3) ? view_decks(decks)
        : (opt == 4) ? create_card()
        : (opt == 5) ? create_deck(lib)
        : (opt == 6) ? Sim().play(decks)
        : (opt == 7) ? Sim().sim(decks)
        :              PASS
         );

  }
  return 0;
}
