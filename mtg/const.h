// CONST

#ifndef const_h
#define const_h

#include "def.h"


const str
  BOTS_DIR  = "obj/bots"
, CARDS_DIR = "obj/lib"
, DECKS_DIR = "obj/decks"


, MAIN_OPS =
    "(0) Exit\n"
    "(1) Update Library\n"
    "(2) View Library\n"
    "(3) View Decks\n"
    "(4) Create Card\n"
    "(5) Create Deck\n"
    "(6) Play Game\n"
    "(7) Sim Game\n"
    "(8) Sim Games\n"
    "  > "

, SIM_OPS =
    "(0)   Exit\n"
    "(1)   Back\n"
    "(2)   Ready\n"
    "(3 #) View\n"


, GEN_HEADER =
    "/*********************************************************/"
    "/**************** BEGIN GENERATED SECTION ****************/"
    "/*********************************************************/"
, GEN_FOOTER =
    "/*********************************************************/"
    "/****************  END GENERATED SECTION  ****************/"
    "/*********************************************************/"
;


enum Format { EDH, STA, MOD, DRA, SEA, THG };
map<Format, str>
  FORMATS
{ {EDH, "Commander"}
, {STA, "Standard"}
, {MOD, "Modern"}
, {DRA, "Draft"}
, {SEA, "Sealed"}
, {THG, "Two-Headed Giant"}
}

, DECK_DIRS
{ {EDH, DECKS_DIR+"/edh"}
, {STA, DECKS_DIR+"/sta"}
, {MOD, DECKS_DIR+"/mod"}
, {DRA, DECKS_DIR+"/dra"}
, {SEA, DECKS_DIR+"/sea"}
, {THG, DECKS_DIR+"/thg"}
};

enum Type { ART, BAS, CRE, ENC, INS, LAN, LEG, PLA, SOR };
map<Type, str>
  TYPES
{ {ART, "Artifact"}
, {BAS, "Basic"}
, {CRE, "Creature"}
, {ENC, "Enchantment"}
, {INS, "Instant"}
, {LAN, "Land"}
, {LEG, "Legendary"}
, {PLA, "Planeswalker"}
, {SOR, "Sorcery"}
};


#endif
