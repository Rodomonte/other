// CONST

#ifndef const_h
#define const_h

#include "macro.h"

const string
  MAIN_OPS =
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

, GEN_HEADER =
    "/*********************************************************/"
    "/**************** BEGIN GENERATED SECTION ****************/"
    "/*********************************************************/"
, GEN_FOOTER =
    "/*********************************************************/"
    "/****************  END GENERATED SECTION  ****************/"
    "/*********************************************************/"
;

enum Format {
  EDH
, MODERN
};

const str ART = "Artifact"
        , BAS = "Basic"
        , CRE = "Creature"
        , ENC = "Enchantment"
        , INS = "Instant"
        , LAN = "Land"
        , LEG = "Legendary"
        , PLA = "Planeswalker"
        , SOR = "Sorcery";

#endif
