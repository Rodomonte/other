// EVENT

#ifndef event_hh
#define event_hh


enum EventType {
  CAST
, ABILITY
, ATTACK
, BLOCK
};

struct Event {
  EventType type;
  int qual;
  Card& c;
};


#endif
