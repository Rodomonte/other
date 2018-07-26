// MAIN

#include "simn.h"
#include "view.h"
#include "create.h"

int update_lib(){
  int r;
  printf("Pulling data from web..\n");
  r = call("python3 scrape.py");
  if(r == 2) printf("Generating card objects..\n"),
             r = call("python3 parse.py");
  if(r == 2) printf("Writing library..\n"),
             r = call("python3 gen_lib.py");
  return r;
}

int main(){
  int o,r;

  while(1){
    o = -1;
    while(o < 0 || o > 4){
      printf(MAIN_OPS);
      try{ scanf("%d", &o); }catch(...){}
    }

    if     (o == 0) break;
    else if(o == 1) r = update_lib();
    else if(o == 2) r = view_lib
    else if(o == 3) r = view_decks();
    else if(o == 4) r = create_card();
    else if(o == 5) r = create_deck();
    else if(o == 6){ Sim s; r = s.run(); }
    else if(o == 7){ Sim s; r = s.run(); }
    else if(o == 8){ Simn s; r = s.run(); }

    if(!r) break;
  }
  return 0;
}
