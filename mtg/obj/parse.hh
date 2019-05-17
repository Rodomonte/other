// PARSE

#ifndef parse_hh
#define parse_hh

#include "../game/card.hh"


const char* lpath = "../obj/lib/lib.json";

int iii;
str sss;

str next(){
  int n;
  str s;
  s = sss.substr(iii, sss.find(":")-iii);
  iii = sss.find("{", iii)+1, n = 1;
  while(n){
    if(sss[iii] == '{') ++n;
    else if(sss[iii] == '}') --n;
    s.append(1, sss[iii]);
    ++iii;
  }
  return s;
}

stat parse(vec<Card>& lib){
  int n;
  FILE* fp;

  fp = fopen(lpath, "r");
  if(fp == NULL) printf(":(\n");
  fseek(fp, 0, SEEK_END);
  n = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  fread(buf, sizeof(char), n, fp);
  fclose(fp);
  sss = buf, iii = sss.find("\"");

  printf("%s\n", next().c_str());

  return PASS;
}


#endif
