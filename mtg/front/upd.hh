// UPDATE

#ifndef update_h
#define update_h

#include "parse.h"


int update_lib(vc& lib){
  printf("Pulling data from web..\n");
  check(call("python3 pull.py"));
  printf("Generating card objects..\n");
  check(parse(lib));
  return 0;
}


#endif
