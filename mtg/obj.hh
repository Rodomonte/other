// OBJ

#ifndef obj_hh
#define obj_hh

#include "util.hh"


enum ActionType {
  DRAW
, CAST
, ATTACK
, BLOCK
};

enum Subject {
  YOU
, ANY_PLAYER
, ANY_CREATURE
}

enum Object {
  NONE
, YOU
, X_TARGET_PLAYERS
, X_TARGET_CREATURES
, X_TARGET_CREATURES_OR_PLANESWALKERS
};

struct Action {
  int subject_x, object_x;
  ActionType action;
  Subject subject;
  Object object;
  uset<Condition> conditions;
};

struct Sleeve;

struct Quality {
  Action trigger;
  vec<Action> actions;
  Sleeve* owner;
};


struct Card {
  int            bpow, btuf;
  str            name;
  vec<Quality>   quals;
  uset<str>      types;
  umap<str, int> cost;

  Card(){}
  Card(str& _name, int _bpow, int _btuf, uset<str>& _types, uset<str>& _quals,
       umap<str, int>& _cost): name(name), bpow(_bpow), btuf(_btuf),
       types(_types), quals(_quals), cost(_cost) {}

  str string(){
    int i;
    uset<str>::iterator jt;
    umap<str, int>::iterator it;

    sprintf(buf, "%s (", name.c_str());
    for(i = 0; buf[i] != '('; ++i);
    for(it = cost.begin(); it != cost.end(); ++it){
      sprintf(buf+i+1, "%d%s ", it->second, it->first.c_str());
      ++i;
      while(buf[i] != ' ') ++i;
    }
    sprintf(buf+i+1, ") "), i += 2;

    if(types.find("Creature") != types.end()){
      sprintf(buf+i+1, "%d/%d ", bpow, btuf);
      ++i;
      while(buf[i] != ' ') ++i;
    }

    for(jt = types.begin(); jt != types.end(); ++jt){
      sprintf(buf+i+1, "%s ", jt->c_str());
      ++i;
      while(buf[i] != ' ') ++i;
    }

    //! quals
    return str(buf);
  }

  int cmc(){
    int n;
    umap<str, int>::iterator it;
    for(it = cost.begin(), n = 0; it != cost.end(); ++it)
      n += it->second;
    return n;
  }

  bool perm(){
    return in("Artifact", types) || in("Creature", types) ||
           in("Enchantment", types) || in("Land", types);
  }
  bool nlperm(){ return perm() && !in("Land", types); }
};


struct Sleeve {
  bool tapped, attacking;
  Card card;
  umap<str, int> counter;

  Sleeve(Card& c): card(c), tapped(false), attacking(false) {}
};


struct Deck {
  Format format;
  str name;
  vec<Card> main, side, extra;

  Deck(Format f): format(f) {}

  void shuffle(){
    int i,j;
    Card c;
    for(i = main.size()-1; i > 0; --i)
      j = rand()%(i+1), c = main[i], main[i] = main[j], main[j] = c;
  }

  str string(){
    int i;
    str s;
    umap<str, int> m;
    umap<str, int>::iterator it;

    for(i = 0; i < main.size(); ++i){
      if((it = m.find(main[i].name)) == m.end())
        m[main[i].name] = 1;
      else ++it->second;
    }

    s += name + str(":\n");
    for(it = m.begin(); it != m.end(); ++it)
      s += str("x") + std::to_string(it->second) + str(" ") + it->first +
           str("\n");
    return s;
  }
};


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


#endif
