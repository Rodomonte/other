// GAME

#ifndef game_hh
#define game_hh

#include "obj.hh"


struct Game;

struct Bot {
  int life;
  Deck deck;
  vec<Sleeve> library, hand, field, grave, exile;

  Bot(Deck& d): deck(d) {}

  virtual void main1(Game& g) = 0;
  virtual void attack(Game& g) = 0;
  virtual void block(Game& g) = 0;
  virtual void main2(Game& g) = 0;
  virtual void respond(Game& g, Card& c) = 0;
};


struct Game {
  int player, turn;
  Format format;
  vec<Bot*> bot;

  Game(vec<Bot*>& b): bot(b) {

  }

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

  void draw(int p, int n){
    int i;
    umap<str, MultiCard>::iterator it;
    if(bot[p].deck.main.size() < n){
      kill(p
      return;
    }
    for(i = 0; i < n; ++i){
      if((it = hand[p].find(deck[p].main.back().name)) == hand[p].end())
        hand[p][deck[p].main.back().name] = MultiCard(deck[p].main.back());
      else ++it->second.n;
      deck[p].main.pop_back();
    }
  }

  void init(){
    int i;
    turn = 0;
    for(i = 0; i < bot.size(); ++i)
      life.pb((format == EDH) ? 40 : 20);
    //check(init_log());
    player = rand() % bot.size();
    for(i = 0; i < bot.size(); ++i)
      draw(i, 7);
  }

  void play(){
    init();
    while(!done()){
      //! upkeep
      if(turn > 1) draw(player, 1);
      bot[player]->main1(*this);
      bot[player]->attack(*this);
      //! blocks
      bot[player]->main2(*this);
      //! end
    }
  }
};


struct Human : Bot {
  Human(Deck& d): Bot(d) {}

  void main1(Game& g){
    //!
  }

  void attack(Game& g){
    //!
  }

  void block(Game& g){
    //!
  }

  void main2(Game& g){
    //!
  }

  void respond(Game& g, Card& c){
    //!
  }
};


struct AI : Bot {
  AI(Deck& d): Bot(d) {}

  void main1(Game& g){
    //!
  }

  void attack(Game& g){
    //!
  }

  void block(Game& g){
    //!
  }

  void main2(Game& g){
    //!
  }

  void respond(Game& g, Card& c){
    //!
  }
};


#endif
