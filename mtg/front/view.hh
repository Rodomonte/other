// VIEW

#ifndef view_hh
#define view_hh

#include "../obj/parse.hh"
#include "../game/deck.hh"


stat view_lib(){
  umap<str, Card>::iterator it;
  printf("\nLIBRARY:\n");
  for(it = card_lib.begin(); it != card_lib.end(); ++it)
    printf("%s\n", it->second.string().c_str());
  printf("\n");
  return PASS;
}

stat view_decks(){
  int i, opt;
  while(1){
    opt = -1;
    while(opt < 0 || opt > deck_lib.size()+1){
      printf("\nDECKS:\n(0) Exit\n(1) Back\n");
      for(i = 0; i < deck_lib.size(); ++i)
        printf("(%d) %lu-card deck\n", i+2, deck_lib[i].main.size());
      printf("  > ");
      try{ scanf("%d", &opt); }catch(...){}
    }

    i = 1;
    switch(opt){
      case 0: check(KILL); break;
      case 1: i = 0;       break;
      default: printf("\n%s\n", deck_lib[opt-2].string().c_str()); break;
    }
    if(!i) break;
  }
  return PASS;
}


#endif
