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
  iii = sss.find("{", iii)+1, s = "{", n = 1;
  while(n){
    if(sss[iii] == '{') ++n;
    else if(sss[iii] == '}') --n;
    s.append(1, sss[iii]);
    ++iii;
  }
  return s;
}

Card fill(umap<str, str> m){
  int i,j;
  str s,t;
  Card c;
  vec<str> v;
  umap<str, int>::iterator it;

  c.name = m["name"];
  s = m["manaCost"];
  for(i = 0; i < s.size(); ++i)
    if(s[i] == '{'){
      for(j = i+1, t = ""; s[j] != '}'; ++j)
        t.append(1, s[j]);
      if(isnum(t)) c.cost["A"] = str2int(t);
      else if((it = c.cost.find(t)) == c.cost.end()) c.cost[t] = 1;
      else ++it->second;
    }

  v = json2vec(m["types"]) + json2vec(m["subtypes"]) +
      json2vec(m["supertypes"]);
  for(i = 0; i < v.size(); ++i)
    c.types.insert(v[i]);
  c.quals.insert(m["text"]);
  c.bpow = (m.find("power") == m.end()) ? 0 : str2int(m["power"]);
  c.btuf = (m.find("toughness") == m.end()) ? 0 : str2int(m["toughness"]);
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
  while(sss.find("{", iii) != str::npos)
    lib.pb(fill(json2umap(next())));
  return PASS;
}


#endif
