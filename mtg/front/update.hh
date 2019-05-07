// UPDATE

#ifndef update_hh
#define update_hh

#include "../core/util.hh"
//#include "../obj/parse.hh"


stat update_lib(vec<Card>& lib){
  printf("Pulling data from web..\n");
  check(call("python3 pull.py"));
  printf("Generating card objects..\n");
  //check(parse(lib));
  return 0;
}


#endif
