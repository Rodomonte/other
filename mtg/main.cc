// MAIN

#include "create.h"
#include "load.h"
#include "sim.h"
#include "update.h"
#include "view.h"


vc lib;
vd decks;

int main(){
  int op, r;

  load_lib(lib);
  load_decks(decks);

  while(1){
    op = -1;
    while(op < 0 || op > 4){
      printf("%s", MAIN_OPS);
      try{ scanf("%d", &op); }catch(...){}
    }

    check((op == 0) ? 1
        : (op == 1) ? update_lib(lib)
        : (op == 2) ? view_lib(lib)
        : (op == 3) ? view_decks(decks)
        : (op == 4) ? create_card()
        : (op == 5) ? create_deck(lib)
        : (op == 6) ? Sim().play(decks)
        : (op == 7) ? Sim().sim(decks)
        :             0
         );

  }
  return 0;
}
