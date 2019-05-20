// UTIL

#ifndef util_hh
#define util_hh

#include "const.hh"


char buf[64000000]
   , err[2048];


void quit(const char* file, const char* fn){
  printf("Exiting from %s::%s\n", file, fn);
  exit(0);
}

#define kill() quit(__FILE__, __FUNCTION__);

enum stat {
  KILL
, BACK
, PASS
};

void check(stat s){ if(s == KILL) kill(); }

stat call(const char* cmd){
  int r;
  r = system(cmd);
  return (WIFEXITED(r) && !WEXITSTATUS(r)) ? PASS : KILL;
}

bool in(str& s, uset<str>& u){
  return u.find(s) != u.end();
}

template <typename T>
vec<T> operator+(const vec<T>& a, const vec<T>& b){
  vec<T> v(a);
  v.insert(v.end(), b.begin(), b.end());
  return v;
}

bool isnum(str s){
  int i,d;
  for(i = 0; i < s.size(); ++i)
    if(s[i] < '0' || s[i] > '9') return false;
  return true;
}

int str2int(str s){
  char c,f;
  int i,n;
  c = s[0], f = 1, i = n = 0;
  while(c != '-' && (c < '0' || c > '9')) c = s[++i];
  if(c == '-') f = -1, c = s[++i];
  while(c >= '0' && c <= '9') n = (n<<3) + (n<<1) + c - '0', c = s[++i];
  return n * f;
}

vec<str> json2vec(str s){
  int i,j;
  vec<str> v;
  i = j = 0;
  while(1){
    i = s.find("\"", j+1);
    if(i == str::npos) break;
    j = s.find("\"", i+1);
    if(j == str::npos) break;
    v.pb(s.substr(i+1, j));
  }
  return v;
}

umap<str, str> json2umap(str s){
  int i,j;
  str k;
  umap<str, str> m;
  i = j = 0;
  while(1){
    i = s.find("\"", j+1);
    if(i == str::npos) break;
    j = s.find("\"", i+1);
    if(j == str::npos) break;
    k = s.substr(i+1, j-i-1);
    i = j+3;
    if(s[i] == '"') j = s.find("\"", i+1), ++i;
    else if(s[i] == '[') j = s.find("]", i+1);
    else continue;
    m[k] = s.substr(i, j-i);
  }
  return m;
}


#endif
