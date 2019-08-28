// PARSE

#ifndef parse_hh
#define parse_hh

#include "obj.hh"


const char* lpath = "../obj/lib/lib.json";

void parse_quals(Card& c, str s){
  int i,j;
  for(i = 0, j = -1; i < s.size(); ++i)
    if(s[i] == '\n' || s[i] == '('){
      if(i > j) c.quals.insert(s.substr(j+1, i-j-1));
      if(s[i] == '('){
        while(s[i] != ')') ++i;
        j = i+1;
      }
      else j = i;
    }
  if(j < (int)s.size()-1) c.quals.insert(s.substr(j+1, s.size()-j-1));
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
  c.bpow = (m.find("power") == m.end()) ? 0 : str2int(m["power"]);
  c.btuf = (m.find("toughness") == m.end()) ? 0 : str2int(m["toughness"]);
  parse_quals(c, m["text"]);
  return c;
}

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
  return replace(s, "\\n", "\n");
}

// JSON -> Card objects
void parse(){
  FILE* fp;
  int n;
  str s;
  Card c;

  fp = fopen(lpath, "r");
  fseek(fp, 0, SEEK_END);
  n = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  fread(buf, sizeof(char), n, fp);
  fclose(fp);

  printf("Generating card objects..\n");
  sss = buf, iii = 0;
  while(sss.find("{", iii) != str::npos){
    c = fill(json2umap(next()));
    card_lib[c.name] = c;
  }
}


#endif
