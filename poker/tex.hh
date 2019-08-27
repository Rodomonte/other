// TEXAS HOLD EM

#include "bot.hh"


struct betcmp {
  vec<bot*> bots;
  betcmp(vec<bot*>& _bots): bots(_bots) {}
  bool operator()(int i, int j) const {
    return bots[i]->bet > bots[j]->bet;
  }
};

struct tex {
  int ante, blind, p1, bet;
  hand board;
  deck d;
  vec<bot*> bots;
  vec<pot> pots;

  tex(vec<bot*> _bots, int _ante, int _blind):
    bots(_bots), ante(_ante), blind(_blind), p1(0) {}

  // Returns true if hand is over
  bool betone(int i){
    bool f;
    int j,c;
    for(j = 0, f = true; j < bots.size(); ++j)
      if(i != j && !bots[j]->out){ f = false; break; }
    if(f) return true;
    c = bots[i]->bet_tex(this);
    if(c == -1){ bots[i]->out = true; return false; }
    bots[i]->pay(c);
    if(bots[i]->bet > bet) bet = bots[i]->bet;
    return false;
  }

  //! Pots created incorrectly on bets that folded
  // Returns true if hand is over
  bool betround(){
    bool f, done;
    int i,j,n;
    vec<int> v;
    vec<pot> pots2;

    // Place bets
    done = false;
    for(i = p1; i < bots.size(); ++i)
      if(!bots[i]->out && betone(i))
        done = true;
    for(i = 0; i < p1; ++i)
      if(!bots[i]->out && betone(i))
        done = true;
    for(i = 0; i < bots.size(); ++i)
      if(!bots[i]->out) v.pb(i);
    std::sort(v.begin(), v.end(), betcmp(bots));

    // Create new pots
    while(!v.empty()){
      pot p;
      for(i = 0; i < v.size(); ++i)
        p.players.pb(v[i]);
      n = bots[v.back()]->bet;
      for(i = 0; i < v.size(); ++i)
        p.cash += n, bots[v[i]]->bet -= n;
      while(!v.empty() && !bots[v.back()]->bet)
        v.pop_back();
      pots2.pb(p);
    }

    // Merge new pots into existing
    for(i = 0; i < pots2.size(); ++i){
      for(j = 0, f = false; j < pots.size(); ++j){
        if(pots2[i] == pots[j]){
          pots[j].cash += pots2[i].cash;
          f = true;
          break;
        }
      }
      if(!f) pots.pb(pots2[i]);
    }

    // Clear bets
    for(i = 0; i < bots.size(); ++i)
      bots[i]->bet = 0;
    return done;
  }

  void play(){
    bool f;
    int i,j,k,t;
    vec<int> winners;

    t = 0;
    while(bots.size() > 1){
      ++t;
      printf("\nTURN %d:\n(%d", t, bots[0]->cash);
      for(i = 1; i < bots.size(); ++i)
        printf(", %d", bots[i]->cash);
      printf(")\n");

      // Rejoin players
      for(i = 0; i < bots.size(); ++i)
        bots[i]->out = false;

      // Pay blinds
      i = (p1-1 < 0) ? p1-1+bots.size() : p1-1;
      j = (p1-2 < 0) ? p1-2+bots.size() : p1-2;
      bots[i]->pay(blind);
      bots[j]->pay(blind >> 1);
      bet = blind;

      // Deal hands
      d = DECK, d.shuf(), board.clear();
      for(j = 0; j < bots.size(); ++j)
        bots[j]->hand.clear();
      for(i = 0; i < 2; ++i)
        for(j = 0; j < bots.size(); ++j)
          bots[j]->hand.pb(d.draw());

      // Bet and show
      f = betround();
      if(!f){
        d.draw();
        for(i = 0; i < 3; ++i)
          board.pb(d.draw());
        printf("\nFLOP: %s\n", board.string().c_str());
        f = betround();
        if(!f){
          d.draw();
          board.pb(d.draw());
          printf("\nTURN: %s\n", board.string().c_str());
          f = betround();
          if(!f){
            d.draw();
            board.pb(d.draw());
            printf("\nRIVER: %s\n\n", board.string().c_str());
            betround();
          }
        }
      }

      // Award pots
      for(i = 0; i < pots.size(); ++i){
        winners.clear();
        for(j = 0; j < pots[i].players.size(); ++j){
          for(k = 0, f = true; k < pots[i].players.size(); ++k)
            if(j != k && bots[pots[i].players[j]]->hand.cmp(
                         bots[pots[i].players[k]]->hand) == -1){
              f = false; break; }
          if(f) winners.pb(pots[i].players[j]);
        }
        for(j = 0; j < winners.size(); ++j){
          k = pots[i].cash / winners.size();
          bots[winners[j]]->cash += k;
          printf("Bot %d won %d\n", winners[j], k);
        }
      }
      pots.clear();

      // Remove players
      for(i = 0; i < bots.size(); ++i){
        if(!bots[i]->cash){
          bots.erase(bots.begin() + i);
          if(p1 >= i) p1 = (p1-1 < 0) ? bots.size()-1 : p1-1;
          i = 0;
        }
      }

      // Rotate dealer
      p1 = (p1 == bots.size()-1) ? 0 : p1+1;
      getchar();
    }
  }

  // Given a 2-card hand, 0-5 card board, and number of players:
  // % chance of winning
  // % chance of getting certain hand
  void sim(texhand h, texhand b, int p){
    int i,j,k,m,n,w,t, p1,p2,k3,st,fl,fh,k4,sf,rf;
    texhand hn,bn;
    deck d,d0;
    vec<texhand> ph;

    d0 = DECK;
    for(i = 0; i < h.size(); ++i)
      d0.erase(h[i]);
    for(i = 0; i < board.size(); ++i)
      d0.erase(b[i]);

    w = t = p1 = p2 = k3 = st = fl = fh = k4 = sf = rf = 0;
    for(k = 0; k < 10000000; ++k){
      d = d0, d.shuf();
      ph.clear(), ph.pb(h);
      for(i = 0; i < p-1; ++i)
        hn.clear(), hn.pb(d.draw()), hn.pb(d.draw()), ph.pb(hn);
      bn = b;
      for(i = 0; i < HN-board.size(); ++i)
        bn.pb(d.draw());

      hn = ph[0];
      for(i = 0; i < bn.size(); ++i)
        hn.pb(bn[i]);
      if(!hn.rf().empty()) ++rf;
      else if(!hn.sf().empty()) ++sf;
      else if(!hn.kind(4).empty()) ++k4;
      else if(!hn.fh().empty()) ++fh;
      else if(!hn.fl().empty()) ++fl;
      else if(!hn.st().empty()) ++st;
      else if(!hn.kind(3).empty()) ++k3;
      else if(!hn.pair2().empty()) ++p2;
      else if(!hn.kind(2).empty()) ++p1;

      for(i = 0; i < p; ++i)
        for(j = 0; j < HN; ++j)
          ph[i].pb(bn[j]);
      m = 1;
      for(i = 1; i < p; ++i){
        n = ph[0].cmp(ph[i]);
        if(n < m) m = n;
        if(m == -1) break;
      }
      if(m == 1) ++w;
      if(m == 0) ++t;

      printf("\n----------------\n\n");
      printf("%.2lf%% win\n",          (double)w / (k+1) * 100);
      printf("%.2lf%% tie\n\n",            (double)t / (k+1) * 100);
      printf("%.2lf%% royal flush\n",    (double)rf / (k+1) * 100);
      printf("%.2lf%% straight flush\n", (double)sf / (k+1) * 100);
      printf("%.2lf%% 4 of a kind\n",    (double)k4 / (k+1) * 100);
      printf("%.2lf%% full house\n",     (double)fh / (k+1) * 100);
      printf("%.2lf%% flush\n",          (double)fl / (k+1) * 100);
      printf("%.2lf%% straight\n",       (double)st / (k+1) * 100);
      printf("%.2lf%% 3 of a kind\n",    (double)k3 / (k+1) * 100);
      printf("%.2lf%% 2 pair\n",         (double)p2 / (k+1) * 100);
      printf("%.2lf%% pair\n",           (double)p1 / (k+1) * 100);
    }
  }
};


int human::bet_tex(tex* g){
  int n,o;
  o = 0;
  while(o < 1 || o > 3){
    printf("\nYou have %s and %d cash\n"
           "Bet is at %d\n"
           "(1) Raise\n"
           "(2) Call %d\n"
           "(3) Fold\n"
           "> ",
           hand.string().c_str(), cash, g->bet, g->bet - bet);
    scanf("%d", &o);
  }
  if(o == 1){
    printf("Raise to ");
    scanf("%d", &n);
    return n - bet;
  }else if(o == 2) return g->bet - bet;
  else return -1;
}


int ai::bet_tex(tex* g){
  //!
  return -1;
}
