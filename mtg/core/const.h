// CONST

#ifndef const_h
#define const_h

#include "obj.h"


const str
  BOTS_DIR  = "obj/bots"
, LIB_DIR   = "obj/lib"
, DECKS_DIR = "obj/decks"

, LIB_JSON  = LIB_DIR.join("lib.json")

, MAIN_OPS =
    "(0) Exit\n"
    "(1) Update Library\n"
    "(2) View Library\n"
    "(3) View Decks\n"
    "(4) Create Card\n"
    "(5) Create Deck\n"
    "(6) Play Game\n"
    "(7) Sim Games\n"
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


enum Format { EDH, DRA, MOD, SEA, STA, THG };
map<Format, str>
  FORMATS
{ {DRA, "Draft"}
, {EDH, "Commander"}
, {MOD, "Modern"}
, {SEA, "Sealed"}
, {STA, "Standard"}
, {THG, "Two-Headed Giant"}
}

, DECK_DIRS
{ {DRA, DECKS_DIR+"/lim"}
, {EDH, DECKS_DIR+"/edh"}
, {MOD, DECKS_DIR+"/mod"}
, {SEA, DECKS_DIR+"/lim"}
, {STA, DECKS_DIR+"/sta"}
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
