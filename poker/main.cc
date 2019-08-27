// POKER CONSOLE

#include "tex.hh"


int main(){
  init();

  int i;
  vec<bot*> bots;
  bots.pb(new human(1000));
  for(i = 0; i < 8; ++i)
    bots.pb(new ai(1000));
  tex g(bots, 0, 20);

  g.play();
  //g.sim(texhand({CK, SK}), texhand({CJ, CT}), 2);

  return 0;
}
