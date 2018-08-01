// UTIL

#ifndef util_h
#define util_h

#include "obj.h"


#define kill() quit(__FILE__, __FUNCTION__);

#define check(r) if(!r || r == 1) return r;

void quit(const char* file, const char* fn){
  printf("Exiting from %s::%s\n", file, fn);
  exit(0);
}

str file2str(str file){
  int n;
  FILE* fp;
  fp = fopen(file.c_str(), "r");
  fseek(fp, 0, SEEK_END);
  n = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  fread(buf, n, 1, fp);
  fclose(fp);
  return str(buf);
}

void str2file(str file, str s){
  FILE* fp;
  fp = fopen(file.c_str(), "w");
  fprintf(fp, "%s\n", s.c_str());
  fclose(fp);
}

int call(str cmd){
  int r;
  r = system(cmd);
  return (WIFEXITED(r) && !WEXITSTATUS(r)) ? 2 : 0;
}


#endif
