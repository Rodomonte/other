// GAME

#ifndef game_hh
#define game_hh

#include "deck.hh"
#include "bot.hh"


struct MultiCard {
  int n;
  Card c;
  MultiCard(Card& _c): c(_c), n(1) {}
};

struct Game {
  int       cp, turn;
  Format    format;
  vec<int>  life;
  vec<Bot>  bot;
  vec<Deck> deck;
  vec<umap<str, MultiCard> > hand, field, grave, exile;

  Game(){}
  Game(Format _format, vec<Bot>& _bot, vec<Deck>& _deck):
      format(_format), bot(_bot), deck(_deck) { init(); }

  str string(){
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
    for(i = n = 0; i < life.size(); ++i) if(!life[i]) n += 1;
    return n >= life.size()-1;
  }

  stat draw(Deck& d, umap<str, Card> m, int n){
    int i;
    for(i = 0; i < n; ++i){
      //if(!d.empty())
    }
    return PASS;
  }

  stat init(){
    int i;
    turn = 0;
    for(i = 0; i < deck.size(); ++i)
      life.pb((format == EDH) ? 40 : 20);
    //check(init_log());

    cp = rand() % life.size();
    for(i = 0; i < life.size(); ++i)
      check(draw(deck[i], hand[i], 7));

    return PASS;
  }

  stat step(){

    //! write file
    return PASS;
  }

  stat run(){
    check(init());
    while(1){
      check(step());
      //check(log(to_str()));
      if(done()) break;
    }
    return PASS;
  }
};


#endif
