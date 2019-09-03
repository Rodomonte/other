// POKER CONSOLE

#include "sim.hh"


int main(){
  init();

  //DBG = true;
  tex g(50);
  g.sim();

  // int i;
  // tex g(20);
  // //g.bots.pb(new human(1000));
  // for(i = 0; i < 9; ++i)
  //   g.bots.pb(new ai(1000));
  // g.play();

  // g.simhand(texhand({CK, SK}), texhand({CJ, CT}), 2);

  return 0;
}
