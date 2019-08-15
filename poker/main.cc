// POKER CONSOLE

#include "tex.hh"
//#include "dw.hh"


int main(){
  init();

  tex g;
  // g.sim(texhand({CK, SK}), texhand(), 2);

  int i;
  vec<bot*> bots;
  bots.pb(new human(1000));
  for(i = 0; i < 8; ++i)
    bots.pb(new bot0(1000));
  g.play(bots);

  return 0;
}
