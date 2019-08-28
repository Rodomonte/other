// OBJ

#ifndef obj_hh
#define obj_hh


struct Game;

struct Card {
  int            bpow, btuf;
  str            name;
  uset<str>      types, quals;
  umap<str, int> cost, counters;

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

    for(jt = QUALS.begin(); jt != QUALS.end(); ++jt)
      if(quals.find(*jt) != quals.end()){
        sprintf(buf+i+1, "- %s -", jt->c_str());
        i += 3;
        while(buf[i] != '-') ++i;
      }
    return str(buf);
  }

  int cmc(){
    int n;
    umap<str, int>::iterator it;
    for(it = cost.begin(), n = 0; it != cost.end(); ++it)
      n += it->second;
    return n;
  }

  int pow(Game& g){
    int n;
    umap<str, int>::iterator it;
    for(it = counters.begin(), n = bpow; it != counters.end(); ++it){
      //!
    }
    return n;
  }

  int tuf(Game& g){
    int n;
    umap<str, int>::iterator it;
    for(it = counters.begin(), n = btuf; it != counters.end(); ++it){
      //!
    }
    return n;
  }

  bool perm(){
    return in(TYPES[ART], types) || in(TYPES[CRE], types) ||
           in(TYPES[ENC], types) || in(TYPES[LAN], types);
  }
  bool nlperm(){ return perm() && !in(TYPES[LAN], types); }

  stat load(int id){
    return PASS;
  }

  stat write(){
    return PASS;
  }
};


struct Deck {
  int       id;
  Format    format;
  str       name;
  vec<Card> main, side, extra;

  Deck(){}
  Deck(int _id, Format _format): id(_id), format(_format) {}
  Deck(vec<Card> _main, vec<Card> _side, vec<Card> _extra):
    main(_main), side(_side), extra(_extra) {}

  void shuffle(){
    int i,j;
    Card c;
    for(i = main.size()-1; i > 0; --i)
      j = rand()%(i+1), c = main[i], main[i] = main[j], main[j] = c;
  }

  //str file(){ return str(sprintf(_, "%s/d%4d.deck", DECK_DIRS[format], id)); }

  void from_file(){
    str s;

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

  // void to_file(){
  //   FILE* fp;
  //   fp = fopen(file().c_str(), "w");
  //   //fprintf(
  // }
};


vec<Deck> deck_lib;
umap<str, Card> card_lib;


#endif
