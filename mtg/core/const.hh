// CONST

#ifndef const_hh
#define const_hh

#include "def.hh"


const str
  BOTS_DIR  = "obj/bots"
, LIB_DIR   = "obj/lib"
, DECKS_DIR = "obj/decks"

, LIB_JSON  = LIB_DIR + "/lib.json"

, MAIN_OPTS =
    "(0) Exit\n"
    "(1) Update Library\n"
    "(2) View Library\n"
    "(3) View Decks\n"
    "(4) Create Card\n"
    "(5) Create Deck\n"
    "(6) Play Game\n"
    "(7) Sim Games\n"
    "  > "

, SIM_OPTS =
    "(0) Exit\n"
    "(1) Back\n"
    "(2) EDH\n"
    "(3) Modern\n"
    "  > "

, COLORS = "WUBRG";
;


enum Format
{ EDH, DRA, MOD, SEA, STA, THG };
enum Type
{ ART, BAS, CRE, ENC, INS, LAN, LEG, PLA, SOR };

vec<int>
  DECK_SIZES
{ 100, 40, 60, 40, 60, 40 };

vec<str>
  FORMATS
{ "Commander", "Draft", "Modern", "Sealed", "Standard", "Two-Headed Giant" }
, TYPES
{ "Artifact", "Basic", "Creature", "Enchantment", "Instant", "Land"
, "Legendary", "Planeswalker", "Sorcery" }
, DECK_DIRS
{ DECKS_DIR+"/lim", DECKS_DIR+"/edh", DECKS_DIR+"/mod", DECKS_DIR+"/lim"
, DECKS_DIR+"/sta", DECKS_DIR+"/thg" };

uset<str>
  QUALS
{ "Trample", "Flying", "Deathtouch", "Reach", "Vigilance", "Indestructible"
, "Menace", "Lifelink", "Defender", "Delve", "Investigate", "First strike"
, "Double strike", "Ingest", "Haste", "Flash", "Hexproof", "Prowess"};


#endif
