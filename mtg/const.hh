// CONST

#ifndef const_hh
#define const_hh

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#define ll   long long
#define str  std::string
#define vec  std::vector
#define uset std::unordered_set
#define umap std::unordered_map
#define pb   push_back


enum Format
{ EDH, MOD, STA, LIM, THG };
int LIFE[5] =
{  40,  20,  20,  20,  30 }
  , DECK_MIN[5] =
{ 100,  60,  40,  40,  60 };


// Whenever <Subject> <Action> <Object/Location>
enum Subject
{ NONE

, SELF         // n
, OTHER_PLAYER // n
, ANY_PLAYER

, THIS_CREATURE  // sleeve
, OTHER_CREATURE // sleeve
, ANY_CREATURE

, OWN_CREATURE_OF_TYPE // s
, ANY_CREATURE_OF_TYPE // s

, ANY_PLANESWALKER


, PLAYER_OR_PLANESWALKER
, CREATURE_OR_PLANESWALKER
, THIS_CREATURE      // sleeve
, OTHER_CREATURE     // sleeve
, OWN_CREATURE       // n
, OTHER_OWN_CREATURE // n, sleeve
, ENEMY_CREATURE     // n
};

enum Object
{ NONE

, ONE_PLAYER  // n
, ALL_PLAYERS

, ONE_CREATURE  // sleeve
, ALL_CREATURES

};

enum Location
{ LIBRARY
, HAND
, FIELD
, GRAVE
, EXILE
};

enum Action
{ NONE
, ATTACK
, BLOCK
, CAST
, DRAW
, MOVE
};

struct Event {
  int n;
  str s;
  Identity subject, target;
  Action action;
  Location location;
  Sleeve* sleeve;
};

// vec<str> TYPES
// { "Artifact", "Basic", "Creature", "Enchantment", "Instant", "Land"
// , "Legendary", "Planeswalker", "Sorcery" }

// uset<str>
//   QUALS
// { "Trample", "Flying", "Deathtouch", "Reach", "Vigilance", "Indestructible"
// , "Menace", "Lifelink", "Defender", "Delve", "Investigate", "First strike"
// , "Double strike", "Ingest", "Haste", "Flash", "Hexproof", "Prowess"};


#endif
