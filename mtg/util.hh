// UTIL

#ifndef util_hh
#define util_hh

#include "const.hh"


char buf[64000000]
   , err[2048];

#define assert(b) \
  if(!b){ printf("bad assert in %s::%s\n", __FILE__, __FUNCTION__); exit(0); }

void call(const char* cmd){
  int r = system(cmd);
  if(WIFEXITED(r) && !WEXITSTATUS(r)) return;
  printf("exit from call()\n");
  exit(0);
}

bool in(str& s, uset<str>& u){
  return u.find(s) != u.end();
}

str replace(str s, str t, str n){
  int i;
  while((i = s.find(t)) != str::npos)
    s = s.substr(0, i) + n + s.substr(i+t.size(), s.size()-i-t.size());
  return s;
}

// template <typename T>
// vec<T> operator+(const vec<T>& a, const vec<T>& b){
//   vec<T> v(a);
//   v.insert(v.end(), b.begin(), b.end());
//   return v;
// }

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
    v.pb(s.substr(i+1, j-i-1));
  }
  return v;
}

umap<str, str> json2umap(str s){
  int i,j,t;
  str k;
  umap<str, str> m;
  i = j = 0;
  while(1){
    i = s.find("\"", j+1);
    if(i == str::npos) return m;
    j = s.find("\"", i+1);
    if(j == str::npos) return m;
    k = s.substr(i+1, j-i-1);
    i = j+3, t = i+1;
    if(s[i] == '"'){
      while(1){
        j = s.find("\"", t);
        if(s[j-1] != '\\') break;
        t = j+1;
      }
      ++i;
    }else if(s[i] == '[') j = s.find("]", i+1);
    else continue;
    m[k] = s.substr(i, j-i);
  }
  return m;
}


#endif
