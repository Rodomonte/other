// GAME

#ifndef game_hh
#define game_hh

#include "bot.hh"
#include "deck.hh"


struct MultiCard {
  int n, tapped, attacking;
  Card c;
  MultiCard(Card& _c): c(_c), n(1) {}
};

struct Game {
  int       cp, turn;
  Format    format;
  vec<int>  life;
  vec<Bot*> bot;
  vec<Deck> deck;
  vec<umap<str, MultiCard> > hand, field, grave, exile;

  Game(){}
  Game(Format _format, vec<Bot*>& _bot, vec<Deck>& _deck):
      format(_format), bot(_bot), deck(_deck) { init(); }

  bool cost_sat(Card& c, int t){
    umap<str, int>::iterator it;
    umap<str, MultiCard>::iterator jt;
    for(it = c.cost.begin(); it != c.cost.end(); ++it){
      if(it->first == str("W") &&
         ((jt = field[t].find("Plains")) == field[t].end() ||
          it->second > jt->second.n - jt->second.tapped)) return false;
      if(it->first == str("U") &&
         ((jt = field[t].find("Island")) == field[t].end() ||
          it->second > jt->second.n - jt->second.tapped)) return false;
      if(it->first == str("B") &&
         ((jt = field[t].find("Swamp")) == field[t].end() ||
          it->second > jt->second.n - jt->second.tapped)) return false;
      if(it->first == str("R") &&
         ((jt = field[t].find("Mountain")) == field[t].end() ||
          it->second > jt->second.n - jt->second.tapped)) return false;
      if(it->first == str("G") &&
         ((jt = field[t].find("Forest")) == field[t].end() ||
          it->second > jt->second.n - jt->second.tapped)) return false;
    }
    return true;
  }

  str hand_string(int t){
    str s = "Hand:\n";
    umap<str, MultiCard>::iterator it;
    for(it = hand[t].begin(); it != hand[t].end(); ++it){
      if(cost_sat(it->second.c, t)) s += "** ";
      else s += "   ";
      s += it->second.c.string();
      if(it->second.n > 1)
        s += " x", sprintf(buf, "%d", it->second.n), s += str(buf);
      s += "\n";
    }
    return s;
  }

  str string(){
    str s;
    //!
    return s;
  }

  bool done(){
    int i, n;
    for(i = n = 0; i < life.size(); ++i) if(!life[i]) n += 1;
    return n >= life.size()-1;
  }

  stat draw(int p, int n){
    int i;
    umap<str, MultiCard>::iterator it;
    if(deck[p].main.size() < n) return KILL; //!
    for(i = 0; i < n; ++i){
      if((it = hand[p].find(deck[p].main.back().name)) == hand[p].end())
        hand[p][deck[p].main.back().name] = MultiCard(deck[p].main.back());
      else ++it->second.n;
      deck[p].main.pop_back();
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

  stat run(){
    check(init());
    while(1){
      //check(log(string()));
      if(done()) break;
      //! upkeep
      if(turn > 1)
        draw(cp);
      bot[cp].main1(*this);
      bot[cp].attack(*this);
      //! blocks
      bot[cp].main2(*this);
      //! end
    }
    return PASS;
  }
};


#endif
