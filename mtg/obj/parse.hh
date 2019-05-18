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
  iii = sss.find("\"", iii);
  s = sss.substr(iii, sss.find(":", iii)-iii);
  iii = sss.find("{", iii)+1, n = 1;
  while(n){
    if(sss[iii] == '{') ++n;
    else if(sss[iii] == '}') --n;
    s.append(1, sss[iii]);
    ++iii;
  }
  return s;
}

umap<Cost, int> cost(str s){
  umap<Cost, int> m;

  return m;
}

Card fill(umap<str, str> m){
  int i;
  Card c;
  vec<str> t;
  c.name = m[name];
  c.cost = cost(m["manaCost"]);
  t = json2vec(m["types"]) + json2vec(m["subtypes"]);
  for(i = 0; i < t.size(); ++i)
    c.types.insert(t[i]);
  c.quals.insert(m["text"]);
  c.bpow = str2int(m["power"]);
  c.btuf = str2int(m["toughness"]);
  return c;
}

// JSON -> Card objects
stat parse(vec<Card>& lib){
  FILE* fp;
  int n;
  str s;

  fp = fopen(lpath, "r");
  if(fp == NULL) printf(":(\n");
  fseek(fp, 0, SEEK_END);
  n = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  fread(buf, sizeof(char), n, fp);
  fclose(fp);
  sss = buf, iii = 0;
  while(sss.find("{", iii) != -1)
    lib.pb(fill(json2umap(next())));
  return PASS;
}


#endif
