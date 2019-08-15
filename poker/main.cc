// POKER CONSOLE

#include "the.hh"
//#include "dw.hh"

int main(){
  the g;
  init();

  //g.sim(thehand({CA, SA}), thehand(), 9);

  thehand h({C2, C3, S2, C5, D4, HA});
  thehand s(h.pair2());
  printf("%d\n", s.size());

  return 0;
}
