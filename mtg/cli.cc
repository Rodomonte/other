// MAIN

#include "parse.hh"
#include "sim.hh"


umap<str, Card> card_lib;
vec<Deck> deck_lib;


void update_lib(){
  printf("Pulling data from web..\n");
  call("python3 pull.py");
  parse();
}


void view_lib(){
  umap<str, Card>::iterator it;
  printf("\nLIBRARY:\n");
  for(it = card_lib.begin(); it != card_lib.end(); ++it)
    printf("%s\n", it->second.string().c_str());
  printf("\n");
}


void view_decks(){
  // int i, opt;
  // while(1){
  //   opt = -1;
  //   while(opt < 0 || opt > deck_lib.size()+1){
  //     printf("\nDECKS:\n(0) Exit\n(1) Back\n");
  //     for(i = 0; i < deck_lib.size(); ++i)
  //       printf("(%d) %lu-card deck\n", i+2, deck_lib[i].main.size());
  //     printf("  > ");
  //     try{ scanf("%d", &opt); }catch(...){}
  //   }

  //   i = 1;
  //   switch(opt){
  //     case 0: check(KILL); break;
  //     case 1: i = 0;       break;
  //     default: printf("\n%s\n", deck_lib[opt-2].string().c_str()); break;
  //   }
  //   if(!i) break;
  // }
}


void create_card(){
  //!
}


void create_deck(){
  // char f;
  // int i,j,k;
  // uset<char> scheme;
  // umap<str, Card>::iterator it;
  // umap<str, int>::iterator jt;
  // uset<char>::iterator kt;
  // Deck d;

  // // Determine colors
  // i = rand() % 5 + 1;
  // for(j = 0; j < i; ++j){
  //   while(1){
  //     k = rand() % 5, f = 1;
  //     for(kt = scheme.begin(); kt != scheme.end(); ++kt)
  //       if(*kt == COLORS[k]){ f = 0; break; }
  //     if(f) break;
  //   }
  //   scheme.insert(COLORS[k]);
  // }

  // //! Determine format
  // d.format = MOD;

  // // Add basic lands
  // kt = scheme.begin();
  // while((double)d.main.size() / DECK_SIZES[d.format] < 0.42){
  //   if(kt == scheme.end()) kt = scheme.begin();
  //   switch(*kt){
  //     case 'W': d.main.pb(card_lib["Plains"]);   break;
  //     case 'U': d.main.pb(card_lib["Island"]);   break;
  //     case 'B': d.main.pb(card_lib["Swamp"]);    break;
  //     case 'R': d.main.pb(card_lib["Mountain"]); break;
  //     case 'G': d.main.pb(card_lib["Forest"]);   break;
  //   }
  //   ++kt;
  // }

  // // Add random creatures
  // while(d.main.size() < DECK_SIZES[d.format]){
  //   it = std::next(card_lib.begin(), rand() % card_lib.size()), f = 1;
  //   Card& c(it->second);
  //   for(jt = c.cost.begin(); jt != c.cost.end(); ++jt)
  //     if((jt->first.size() == 1 &&
  //         scheme.find(jt->first.at(0)) == scheme.end()) ||
  //        (jt->first.size() == 3 && scheme.find(jt->first.at(0)) == scheme.end()
  //         && scheme.find(jt->first.at(2)) == scheme.end())){
  //       f = 0; break; }
  //   if(!f || c.types.find("Creature") == c.types.end()) continue;
  //   d.main.pb(c);
  // }

  // // Generate name
  // for(i = 0; i < 16; ++i)
  //   d.name.append(1, (char)(rand() % 26) + 'a');
  // deck_lib.pb(d);
}


int main(){
  int o;

  parse();

  while(1){
    o = -1;
    while(o < 0 || o > 7){
      printf("\n"
             "(0) Exit\n"
             "(1) Update Library\n"
             "(2) View Library\n"
             "(3) View Decks\n"
             "(4) Create Card\n"
             "(5) Create Deck\n"
             "(6) Play Game\n"
             "(7) Sim Games\n"
             "  > ");
      try{ scanf("%d", &o); }catch(...){}
    }

    switch(o){
      case 0: exit(0);       break;
      case 1: update_lib();  break;
      case 2: view_lib();    break;
      case 3: view_decks();  break;
      case 4: create_card(); break;
      case 5: create_deck(); break;
      case 6: Game().play(); break;
      case 7: Sim().sim();   break;
    }

  }
  return 0;
}
