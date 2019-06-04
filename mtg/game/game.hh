// GAME

#ifndef game_hh
#define game_hh

#include "bot.hh"
#include "deck.hh"


struct MultiCard {
  int n;
  Card c;
  MultiCard(Card& _c): c(_c), n(1) {}
};

struct Game {
  int       cp, turn;
  Format    format;
  vec<int>  life;
  vec<Bot*>  bot;
  vec<Deck> deck;
  vec<umap<str, MultiCard> > hand, field, grave, exile;

  Game(){}
  Game(Format _format, vec<Bot*>& _bot, vec<Deck>& _deck):
      format(_format), bot(_bot), deck(_deck) { init(); }

  bool cost_sat(Card& c, int t){
    //!
    return false;
  }

  str string(){
    str s;
    //!
    return s;
  }

  str hand_string(int t){
    str s = "Hand:\n";
    umap<str, MultiCard>::iterator it;
    for(it = hand[t].begin(); it != hand[t].end(); ++it){
      if(/*!*/cost_sat(it->second.c, t)) s += "** ";
      else s += "   ";
      s += it->second.c.string();
      if(it->second.n > 1)
        s += " x", sprintf(buf, "%d", it->second.n), s += str(buf);
      s += "\n";
    }
    return s;
  }

  bool done(){
    int i, n;
    for(i = n = 0; i < life.size(); ++i) if(!life[i]) n += 1;
    return n >= life.size()-1;
  }

  stat draw(Deck& d, umap<str, MultiCard>& m, int n){
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
