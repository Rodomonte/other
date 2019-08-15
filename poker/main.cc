// POKER CONSOLE

#include "tex.hh"
//#include "dw.hh"

int main(){
  tex g;
  init();

  //g.sim(texhand({CA, SA}), texhand(), 9);

  texhand h({C2, S2, D3, S7, D2, CJ, C3});
  texhand s(h.fh());
  printf("%s\n", s.string().c_str());

  return 0;
}
