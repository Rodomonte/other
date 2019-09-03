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
  int blind, p1, bet, ID;
  bot* raiser;
  texhand board;
  deck d;
  vec<bot*> bots, pos, neg;
  vec<pot> pots;

  tex(int _blind): blind(_blind), p1(0) {}

  int active(){
    int i,n;
    for(n = i = 0; i < bots.size(); ++i)
      if(!bots[i]->out) ++n;
    return n;
  }

  // Returns 1 if hand is over, 2 if raise, 0 otherwise
  int betone(int i){
    int j,k,c,n;
    n = active();
    if(n < 2) return 1;
    c = bots[i]->bet_tex(this);
    if(DBG) printf("Bot %d bets %d\n", i, c);

    if(c == -1){
      bots[i]->out = true;
      for(j = 0; j < pots.size(); ++j)
        for(k = 0; k < pots[j].players.size(); ++k)
          if(pots[j].players[k] == i){
            pots[j].players.erase(pots[j].players.begin() + k);
            break;
          }
      return (n < 3) ? 1 : 0;
    }

    bots[i]->pay(c);
    if(bots[i]->bet > bet){
      bet = bots[i]->bet;
      raiser = bots[i];
      return 2;
    }
    return 0;
  }

  // Returns true if hand is over
  bool betround(){
    bool f, done;
    int i,j,m,n,t;
    vec<int> v;
    vec<pot> pots2;

    // Place bets
    i = p1, n = 0, done = false;
    while(n < bots.size()){
      if(bots[i]->out) ++n;
      else{
        t = betone(i);
        if(t == 1){ done = true; break; }
        else if(t == 2) n = 0;
        else ++n;
      }
      i = (i == bots.size()-1) ? 0 : i+1;
    }

    // Create new pots
    for(i = 0; i < bots.size(); ++i)
      if(!bots[i]->out) v.pb(i);
    std::sort(v.begin(), v.end(), betcmp(bots));
    while(!v.empty()){
      pot p;
      for(i = 0; i < v.size(); ++i)
        p.players.pb(v[i]);
      m = bots[v.back()]->bet;
      for(i = 0; i < bots.size(); ++i){
        n = min(m, bots[i]->bet);
        p.cash += n, bots[i]->bet -= n;
      }
      while(!v.empty() && !bots[v.back()]->bet)
        v.pop_back();
      if(DBG) printf("Pot created with %d cash, %d players\n",
                     p.cash, p.players.size());
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
    return done;
  }

  void play(){
    bool f;
    int i,j,k,n,t;
    texhand b;
    vec<int> winners;

    t = 0;
    while(1){
      ++t;
      if(DBG){
        printf("\n----\nTURN %d:\n----\n\n(%d", t, bots[0]->cash);
        for(i = 1; i < bots.size(); ++i)
          printf(", %d", bots[i]->cash);
        printf(")\n");
      }

      // Rejoin players
      for(i = 0; i < bots.size(); ++i)
        bots[i]->out = false;
      raiser = NULL;

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
        if(DBG) printf("\nFLOP: %s\n\n", board.string().c_str());
        bet = 0, f = betround();
        if(!f){
          d.draw();
          board.pb(d.draw());
          if(DBG) printf("\nTURN: %s\n\n", board.string().c_str());
          bet = 0, f = betround();
          if(!f){
            d.draw();
            board.pb(d.draw());
            if(DBG) printf("\nRIVER: %s\n\n", board.string().c_str());
            bet = 0, betround();
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
          n = pots[i].cash / winners.size();
          bots[winners[j]]->cash += n;
          b.clear();
          b.pb(bots[winners[j]]->hand[0]);
          b.pb(bots[winners[j]]->hand[1]);
          for(k = 0; k < board.size(); ++k)
            b.pb(board[k]);
          str s(bots[winners[j]]->string());
          printf("%s won %d with %s\n", s.c_str(), n, b.string().c_str());
        }
      }
      pots.clear();

      // Remove players
      for(i = 0; i < bots.size(); ++i){
        if(!bots[i]->cash){
          if     (bots.size() == 2) bots[i]->score += 50;
          else if(bots.size() == 3) bots[i]->score += 25;
          else if(bots.size() == 4) bots[i]->score += 10;
          else if(bots.size() == 5) bots[i]->score -= 10;
          else if(bots.size() == 6) bots[i]->score -= 20;
          else if(bots.size() == 7) bots[i]->score -= 50;
          else if(bots.size() == 8) bots[i]->score -= 100;
          else if(bots.size() == 9) bots[i]->score -= 200;
          if(bots[i]->score <= 0 && bots[i]->score > -100) neg.pb(bots[i]);
          else if(bots[i]->score > 0) pos.pb(bots[i]);
          printf("\nBot %d has score %d (%d pos, %d neg)\n\n",
                 bots[i]->id, bots[i]->score, pos.size(), neg.size());
          bots.erase(bots.begin() + i);
          if(p1 >= i) p1 = (p1-1 < 0) ? bots.size()-1 : p1-1;
          i = 0;
        }
      }

      // Award winner
      if(bots.size() == 1){
        bots[0]->score += 100;
        pos.pb(bots[0]);
        bots.clear();
        break;
      }

      // Rotate dealer
      p1 = (p1 == bots.size()-1) ? 0 : p1+1;
    }
  }

  void sim(){
    int i;
    ID = 0;
    while(1){
      while(bots.size() < 9 && !neg.empty())
        bots.pb(neg[0]), neg.erase(neg.begin());
      while(bots.size() < 8 && !pos.empty())
        bots.pb(pos[0]), pos.erase(pos.begin());
      while(bots.size() < 9)
        bots.pb(genbot(ID++));
      for(i = 0; i < bots.size(); ++i)
        bots[i]->cash = 1000;
      play();

      printf("---\n");
      for(i = 0; i < pos.size(); ++i)
        printf("%s: score %d\n", pos[i]->string().c_str(), pos[i]->score);
      printf("---\n\n");
    }
  }

  // Given a 2-card hand, 0-5 card board, and number of players,
  // return chance of winning
  float simhand(texhand h, texhand b, int p){
    int i,j,k,m,n,w,t, p1,p2,k3,st,fl,fh,k4,sf,rf;
    texhand hn,bn;
    deck d,d0;
    vec<texhand> ph;

    const int ITER = 100;

    d0 = DECK;
    for(i = 0; i < h.size(); ++i)
      d0.erase(h[i]);
    for(i = 0; i < board.size(); ++i)
      d0.erase(b[i]);

    w = t = p1 = p2 = k3 = st = fl = fh = k4 = sf = rf = 0;
    for(k = 0; k < ITER; ++k){
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

      // printf("\n----------------\n\n");
      // printf("%.2lf%% win\n",          (double)w / (k+1) * 100);
      // printf("%.2lf%% tie\n\n",            (double)t / (k+1) * 100);
      // printf("%.2lf%% royal flush\n",    (double)rf / (k+1) * 100);
      // printf("%.2lf%% straight flush\n", (double)sf / (k+1) * 100);
      // printf("%.2lf%% 4 of a kind\n",    (double)k4 / (k+1) * 100);
      // printf("%.2lf%% full house\n",     (double)fh / (k+1) * 100);
      // printf("%.2lf%% flush\n",          (double)fl / (k+1) * 100);
      // printf("%.2lf%% straight\n",       (double)st / (k+1) * 100);
      // printf("%.2lf%% 3 of a kind\n",    (double)k3 / (k+1) * 100);
      // printf("%.2lf%% 2 pair\n",         (double)p2 / (k+1) * 100);
      // printf("%.2lf%% pair\n",           (double)p1 / (k+1) * 100);

    }
    return (float)w / ITER;
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
  int i,c,m;
  float f,w;
  w = g->simhand(hand, g->board, g->active());
  for(i = 0, c = MAX*cash, f = 1.0f-1.0f/DIV, m = 0; i < DIV-1;
      ++i, c *= SCALE, f -= 1.0f/DIV)
    if(w > f){ m = c; break; }
  if(g->bet - bet > m) return -1;
  if(g->raiser == this) return 0;
  return max(g->bet - bet, m / (6 - g->board.size()));
}
