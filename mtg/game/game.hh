// GAME

#ifndef game_hh
#define game_hh

#include "bot.hh"
#include "log.hh"


struct Game {
  int                   id, np, cp, turn;
  Format                format;
  vec<int>              life;
  vec<Bot>              bot;
  vec<Deck>             deck;
  vec<umap<str, int> >  counters;
  vec<umap<str, Card> > hand, field, grave, exile;

  Game(){}
  Game(Format _format, vec<Bot>& _bots, vd& _decks):
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

  stat draw(vd& d, umap<str, Card> m, int n){
    int i;
    for(i = 0; i < n; ++i){
      if(!d.empty())
    }
    return 0;
  }

  stat init(){
    int i;
    np = bots.size();
    turn = 0;
    for(i = 0; i < np; ++i)
      life.pb((type == EDH) ? 40 : 20);
    check(init_log());

    cp = rand() % np;
    for(i = 0; i < np; ++i)
      check(draw(deck[i], hand[i], 7));

    return 0;
  }

  stat step(){

    //! write file
    return 0;
  }

  stat run(){
    check(init());
    while(1){
      check(step());
      check(log(to_str()));
      if(done()) break;
    }
    return 0;
  }
};


#endif
