// CREATE

#ifndef create_hh
#define create_hh

#include "../game/deck.hh"


stat create_card(){

  return PASS;
}

stat create_deck(){
  char f;
  int i,j,k,ii;
  vec<char> scheme;
  umap<str, Card>::iterator it;
  Deck d;

  // Determine colors
  i = rand() % 5 + 1;
  for(j = 0; j < i; ++j){
    while(1){
      k = rand() % 5, f = 1;
      for(ii = 0; ii < scheme.size(); ++ii)
        if(scheme[ii] == COLORS[k]){ f = 0; break; }
      if(f) break;
    }
    scheme.pb(COLORS[k]);
  }

  //! Determine format
  d.format = MOD;

  // Add lands
  i = 0;
  while((double)d.main.size() / DECK_SIZES[d.format] < 0.42){
    switch(scheme[i]){
      case 'W': d.main.pb(card_lib["Plains"]);   break;
      case 'U': d.main.pb(card_lib["Island"]);   break;
      case 'B': d.main.pb(card_lib["Swamp"]);    break;
      case 'R': d.main.pb(card_lib["Mountain"]); break;
      case 'G': d.main.pb(card_lib["Forest"]);   break;
    }
    i = (i == scheme.size()-1) ? 0 : i+1;
  }

  printf("%d / %d\n", d.main.size(), DECK_SIZES[d.format]);

  // Add random creatures
  while(d.main.size() < DECK_SIZES[d.format]){
    it = std::next(card_lib.begin(), rand() % card_lib.size());
    //! filter
  }

  return PASS;
}


#endif
