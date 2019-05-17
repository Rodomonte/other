// VIEW

#ifndef view_hh
#define view_hh

#include "../obj/parse.hh"
#include "../game/deck.hh"


stat view_lib(vec<Card>& lib){
  int i;
  check(parse(lib));
  printf("\nLIBRARY:\n");
  for(i = 0; i < lib.size(); ++i)
    printf("%s\n", lib[i].string().c_str());
  printf("\n");
  return PASS;
}

stat view_decks(vec<Deck>& decks){

  return PASS;
}


#endif
