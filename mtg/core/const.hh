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
    "(0)   Exit\n"
    "(1)   Back\n"
    "(2)   Ready\n"
    "(3 #) View\n"
    "  > "

, GEN_HEADER =
    "/*********************************************************/"
    "/**************** BEGIN GENERATED SECTION ****************/"
    "/*********************************************************/"
, GEN_FOOTER =
    "/*********************************************************/"
    "/****************  END GENERATED SECTION  ****************/"
    "/*********************************************************/"
;


enum Cost
{ WHI, BLU, BLA, RED, GRE, COL, GEN, X, SNO, WHIBLU, WHIBLA, WHIRED, WHIGRE,
  BLUBLA, BLURED, BLUGRE, BLARED, BLAGRE, REDGRE, WHIGEN2, BLUGEN2, BLAGEN2,
  REDGEN2, GREGEN2, PHYWHI, PHYBLU, PHYBLA, PHYRED, PHYGRE };
enum Format
{ EDH, DRA, MOD, SEA, STA, THG };
enum Type
{ ART, BAS, CRE, ENC, INS, LAN, LEG, PLA, SOR };

vec<str>
  COSTS
, FORMATS
{ "Draft", "Commander", "Modern", "Sealed", "Standard", "Two-Headed Giant" }
, TYPES
{ "Artifact", "Basic", "Creature", "Enchantment", "Instant", "Land",
  "Legendary", "Planeswalker", "Sorcery" }
, DECK_DIRS
{ DECKS_DIR+"/lim", DECKS_DIR+"/edh", DECKS_DIR+"/mod", DECKS_DIR+"/lim",
  DECKS_DIR+"/sta", DECKS_DIR+"/thg" };

void init(){
  int i;
  const char* basic = "WUKRG";
  for(i = 0; i < 5; ++i)
    COSTS.pb(str("" + basic[i]));
  //! COSTS.pb(
}


#endif
