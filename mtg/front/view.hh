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

  return PASS;
}


#endif
