// LIB

#ifndef lib_h
#define lib_h

#include "obj.h"

Card m19076(
  "Supreme Phantom", 0, 1, 0, 0, 0, 0, 1, 1, 3
, {"Creature", "Spirit"}
, {"Flying"
 , "Other Spirits you control get +1/+1."});

Card m19121(
  "Stitcher's Supplier", 0, 0, 1, 0, 0, 0, 0, 1, 1
, {"Creature", "Zombie"}
, {"When Stitcher's Supplier enters the battlefield or dies, "
     "put the top three cards of your library into your graveyard."});

Card m19184(
  "Gift of Paradise", 0, 0, 0, 0, 1, 0, 2, 0, 0
, {"Enchantment", "Aura"}
, {"Enchant land"
 , "When Gift of Paradise enters the battlefield, you gain 3 life."
 , "Enchanted land has \"TAP: Add two mana of any one color.\""});

Card m19215(
  "Draconic Disciple", 0, 0, 0, 1, 1, 0, 1, 2, 2
, {"Creature", "Human", "Shaman"}
, {"TAP: Add one mana of any color."
 , "GEN7, TAP, Sacrifice Draconic Disciple:"
     "Create a 5/5 red Dragon creature token with flying."});

#endif
