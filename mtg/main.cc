// MAIN

#include "simn.h"

int view_lib(){

}

int view_decks(){

}

int main(int argc, char** argv){
  int o,r;

  while(1){
    o = 0;
    while(o < 0 || o > 4){
      printf("(0) Exit\n"
             "(1) View Library\n"
             "(2) View Decks\n"
             "(3) Sim Game\n"
             "(4) Sim Games\n"
             "  > ");
      try{ scanf("%d", &o); }catch{}
    }

    if     (o == 0) break;
    else if(o == 1) r = view_lib();
    else if(o == 2) r = view_decks();
    else if(o == 3){ Sim s; r = s.run(); }
    else if(o == 4){ Simn s; r = s.run(); }

    if(!r) break;
  }
  return 0;
}
