// CREATE

#ifndef create_hh
#define create_hh

#include "../game/deck.hh"


stat create_card(){
  //!
  return PASS;
}

stat create_deck(){
  char f;
  int i,j,k;
  uset<char> scheme;
  umap<str, Card>::iterator it;
  umap<str, int>::iterator jt;
  uset<char>::iterator kt;
  Deck d;

  // Determine colors
  i = rand() % 5 + 1;
  for(j = 0; j < i; ++j){
    while(1){
      k = rand() % 5, f = 1;
      for(kt = scheme.begin(); kt != scheme.end(); ++kt)
        if(*kt == COLORS[k]){ f = 0; break; }
      if(f) break;
    }
    scheme.insert(COLORS[k]);
  }

  //! Determine format
  d.format = MOD;

  // Add basic lands
  kt = scheme.begin();
  while((double)d.main.size() / DECK_SIZES[d.format] < 0.42){
    if(kt == scheme.end()) kt = scheme.begin();
    switch(*kt){
      case 'W': d.main.pb(card_lib["Plains"]);   break;
      case 'U': d.main.pb(card_lib["Island"]);   break;
      case 'B': d.main.pb(card_lib["Swamp"]);    break;
      case 'R': d.main.pb(card_lib["Mountain"]); break;
      case 'G': d.main.pb(card_lib["Forest"]);   break;
    }
    ++kt;
  }

  // Add random creatures
  while(d.main.size() < DECK_SIZES[d.format]){
    it = std::next(card_lib.begin(), rand() % card_lib.size()), f = 1;
    Card& c(it->second);
    for(jt = c.cost.begin(); jt != c.cost.end(); ++jt)
      if((jt->first.size() == 1 &&
          scheme.find(jt->first.at(0)) == scheme.end()) ||
         (jt->first.size() == 3 && scheme.find(jt->first.at(0)) == scheme.end()
          && scheme.find(jt->first.at(2)) == scheme.end())){
        f = 0; break; }
    if(!f || c.types.find("Creature") == c.types.end()) continue;
    d.main.pb(c);
  }

  // Generate name
  for(i = 0; i < 16; ++i)
    d.name.append(1, (char)(rand() % 26) + 'a');
  deck_lib.pb(d);

  return PASS;
}


#endif
