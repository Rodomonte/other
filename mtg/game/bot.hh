// BOT

#ifndef bot_hh
#define bot_hh


struct Bot {
  bool human;
  int turn;

  Bot(): human(false) {}
  Bot(bool _human, int _turn): human(_human), turn(_turn) {}

  stat play_human(Game& g){
    umap<str, MultiCard>& hand(g.hand[turn]);
    umap<str, MultiCard>::iterator it;

    printf("Hand:\n");
    for(it = hand.begin(); it != hand.end(); ++it){
      if(/*!*/cost_sat(it->second.c, g.field[turn])) printf("** ");
      else printf("   ");
      printf("%s", it->second.c.string().c_str());
      if(it->second.n > 1) printf(" x%d", it->second.n);
      printf("\n");
    }

    //!
  }

  stat play_bot(Game& g){
    //!
  }

  stat play(Game& g, int t){
    turn = t;
    if(human) return play_human(g);
    else return play_bot(g);
  }
};


#endif
