// GAME

#ifndef game_hh
#define game_hh

#include "obj.hh"


struct Game {
  int player, turn, out;
  Format format;
  vec<Bot*> bots;

  Game(){ init(); }

  bool cost_sat(Card& c, int t){
    // umap<str, int>::iterator it;
    // umap<str, MultiCard>::iterator jt;
    // for(it = c.cost.begin(); it != c.cost.end(); ++it){
    //   if(it->first == str("W") &&
    //      ((jt = field[t].find("Plains")) == field[t].end() ||
    //       it->second > jt->second.n - jt->second.tapped)) return false;
    //   if(it->first == str("U") &&
    //      ((jt = field[t].find("Island")) == field[t].end() ||
    //       it->second > jt->second.n - jt->second.tapped)) return false;
    //   if(it->first == str("B") &&
    //      ((jt = field[t].find("Swamp")) == field[t].end() ||
    //       it->second > jt->second.n - jt->second.tapped)) return false;
    //   if(it->first == str("R") &&
    //      ((jt = field[t].find("Mountain")) == field[t].end() ||
    //       it->second > jt->second.n - jt->second.tapped)) return false;
    //   if(it->first == str("G") &&
    //      ((jt = field[t].find("Forest")) == field[t].end() ||
    //       it->second > jt->second.n - jt->second.tapped)) return false;
    // }
    // return true;
  }

  void draw(int p, int n){
    int i;
    // if(bots[p].deck.main.size() < n){
    //   kill(p);
    //   return;
    // }
    // for(i = 0; i < n; ++i){
    //   if((it = hand[p].find(deck[p].main.back().name)) == hand[p].end())
    //     hand[p][bots[p].deck.main.back().name] = MultiCard(botdeck[p].main.back());
    //   else ++it->second.n;
    //   bots[p].deck.main.pop_back();
    // }
  }

  void init(){
    int i;
    out = turn = 0;
    for(i = 0; i < bots.size(); ++i)
      bots[i]->life = LIFE[format];
    player = rand() % bots.size();
    for(i = 0; i < bots.size(); ++i)
      draw(i, 7);
  }

  void play(){
    init();
    while(1){
      //! upkeep
      if(turn > 1) draw(player, 1);
      bots[player]->main1(*this);
      bots[player]->attack(*this);
      //! blocks
      bots[player]->main2(*this);
      //! end
      player = (player == bots.size()-1) ? 0 : player+1;
    }
  }

  void sim(){
    //!
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
