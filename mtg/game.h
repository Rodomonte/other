// GAME

#ifndef game_h
#define game_h

#include "deck.h"

struct Game {
  int       n;
  Format    format;
  vec<int>  life, poison;
  vec<Bot>  bots;
  vec<Deck> decks;

  Game(){}
  Game(Format _format, vec<Deck> _decks): format(_format), decks(_decks) {
    int i;
    n = decks.size();
    for(i = 0; i < n; ++i)
      life.pb((type == EDH) ? 40 : 20), poison.pb(0);
  }
};

#endif
