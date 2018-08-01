// MAIN

#include "simn.h"
#include "view.h"
#include "create.h"


int update_lib(){
  printf("Pulling data from web..\n");
  check(call("python3 pull.py"));
  printf("Generating card objects..\n");
  check(call("python3 parse.py"));
  printf("Writing library..\n");
  check(call("python3 gen_lib.py"));
  return 2;
}

int main(){
  int op, r;

  while(1){
    op = -1;
    while(op < 0 || op > 4){
      printf("%s", MAIN_OPS);
      try{ scanf("%d", &op); }catch(...){}
    }

    if     (op == 0)  kill();
    if     (op == 1)  r = update_lib();
    else if(op == 2)  r = view_lib();
    else if(op == 3)  r = view_decks();
    else if(op == 4)  r = create_card();
    else if(op == 5)  r = create_deck();
    else if(op == 6){ Sim s; r = s.run(1); }
    else if(op == 7){ Sim s; r = s.run(0); }
    else if(op == 8){ Simn s; r = s.run(); }

    if(!r) break;
  }
  return 0;
}
