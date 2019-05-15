// SELECT

#ifndef select_hh
#define select_hh

#include "../game/bot.hh"
#include "../game/deck.hh"


stat select_decks(Format format, vec<Deck>& r){
  int       i,n,nd,np,opt;
  FILE*     fp;
  str       s;
  vec<Deck> decks;

  // //! replace with count .deck files in dir
  // fp = fopen(sprintf("%s/n.txt", DECK_DIRS[format]), "r");
  // fscanf(fp, "%d", &nd);
  // fclose(fp);
  // for(i = 0; i < nd; ++i){
  //   //!

  //   fp = fopen(sprintf("%s/d%4d.deck", DECK_DIRS[format], i), "r");
  //   fseek(fp, 0, SEEK_END);
  //   n = ftell(fp);
  //   fseek(fp, 0, SEEK_SET);
  //   fread(buf, n, 1, fp);
  //   fclose(fp);
  //   decks.pb(Deck(str(buf)));
  // }
  // // = (format == EDH) ? edh : modern;

  // while(1){
  //   opt = -1;
  //   while(opt < 0 || opt > decks.size()+2){
  //     printf(SIM_OPTS);
  //     for(i = 0; i < decks.size(); ++i)
  //       printf("(%d)   %s\n", i+4, decks[i].name.c_str());
  //     printf("    > ");
  //     try{ scanf("%d", &opt); }catch(...){}
  //     if(opt == 3)
  //       try{ scanf("%d", &n); n -= 4; }catch(...){}
  //   }

  //   check(opt);
  //   if(opt == 2){
  //     if(r.empty()){ printf("\nNo decks selected!\n\n"); continue; }
  //     if(r.size() == 1){ printf("\nOnly one deck selected!\n\n"); continue; }
  //     break;

  //   }else if(opt == 3){
  //     printf("\n%s:\n\n");
  //     for(i = 0; i < decks[n].main.size(); ++i){
  //       decks[n].main[i].print();
  //       printf("\n");
  //     }
  //     printf("\n");

  //   }else r.pb(decks[n]);
  // }
  return PASS;
}


stat select_bots(vec<Bot>& r){
  return PASS;
}


#endif
