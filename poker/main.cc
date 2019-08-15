// POKER CONSOLE

#include "tex.hh"
//#include "dw.hh"

int main(){
  tex g;
  init();

  g.sim(texhand({CA, SA}), texhand(), 9);

  // texhand h({SA, DA, HA, SQ, CJ, SK, CA});
  // texhand s(h.kind(4));
  // printf("%s\n", s.string().c_str());

  return 0;
}
