// GAME

#ifndef game_h
#define game_h

#include "bot.h"
#include "log.h"


struct Game : Obj {
  int                   id, np, cp, turn;
  Format                format;
  vec<int>              life;
  vec<Bot>              bot;
  vec<Deck>             deck;
  vec<umap<str, int> >  counters;
  vec<umap<str, Card> > hand, field, grave, exile;

  Game(){}
  Game(Format _format, vec<Bot>& _bots, vec<Deck>& _decks):
      format(_format), bots(_bots), decks(_decks) {}

  str to_str(){
    int i;
    str s;
    //! sprintf(buf, ..
    /* s = sprintf("{\"id\": %d, \"np\": %d, \"format\": %s, \"life\": [%d", */
    /*             id, np, FORMATS[format].c_str(), life[0]); */
    /* for(i = 1; i < life.size(); ++i) s += sprintf(", %d", life[i]); */
    /* s += sprintf("], \"poison\": [%d", poison[0]); */
    /* for(i = 1; i < poison.size(); ++i) s += sprintf(", %d", poison[i]); */
    /* s += sprintf("], \"bots\": [%d", bots[0].id); */
    /* for(i = 1; i < bots.size(); ++i) s += sprintf(", %d", bots[i].id); */
    /* s += sprintf("], \"decks\": [%d", decks[0].id); */
    /* for(i = 1; i < decks.size(); ++i) s += sprintf(", %d", decks[i].id); */
    return s;
  }

  bool done(){
    int i, n;
    for(i = n = 0; i < np; ++i) if(!life[i]) n += 1;
    return n >= np-1;
  }

  int draw(vec<Deck>& d, umap<str, Card> m, int n){
    int i;
    for(i = 0; i < n; ++i){
      if(!d.empty())
    }
    return 2;
  }

  int init(){
    int i;
    np = bots.size();
    turn = 0;
    for(i = 0; i < np; ++i)
      life.pb((type == EDH) ? 40 : 20);
    check(init_log());

    cp = rand() % np;
    for(i = 0; i < np; ++i)
      check(draw(deck[i], hand[i], 7));

    return 2;
  }

  int step(){

    //! write file
    return 2;
  }

  int run(){
    check(init());
    while(1){
      check(step());
      check(log(to_str()));
      if(done()) break;
    }
    return 2;
  }
};


#endif
