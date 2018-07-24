// GAME

#ifndef game_h
#define game_h

#include "deck.h"

struct Game {
  int       n;
  GameType  type;
  vec<int>  life, poison;
  vec<Deck> decks;

  Game(GameType _type, vec<Deck> _decks): decks(_decks) {
    int i;
    n = decks.size();
    for(i = 0; i < n; ++i)
      life.pb((type == EDH) ? 40 : 20), poison.pb(0);
  }
};

#endif
