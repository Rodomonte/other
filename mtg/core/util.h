// UTIL

#ifndef util_h
#define util_h

#include "const.h"


#define kill() quit(__FILE__, __FUNCTION__);

#define check(r) if(r == 0) {} \
            else if(r == 2) break; \
            else if(r == 3) continue; \
            else            kill();


struct str : string {
  bool in(str& s){
    int i, j;
    for(i = 0; i < s.size(); ++i){
      for(j = 0; j < this->size(); ++j){
        if(i+j >= s.size()) return false;
        if(s[i] != (*this)[j]) break;
        if(j == this->size()-1) return true;
      }
    }
    return false;
  }

  bool in(vs& v){
    int i;
    for(i = 0; i < v.size(); ++i)
      if(v[i] == *this) return true;
    return false;
  }

  bool in(umap<str, Card>& m){
    umap<str, Card>::iterator it;
    for(it = m.begin(); it != m.end(); ++it)
      if(it->first == *this) return true;
    return false;
  }

  str strip_front(str& strips){
    int i;
    for(i = 0; i < this->size() && str((*this)[i])->in(strips); ++i);
    return this->substr(i, this->size()-i);
  }
  str strip_end(str& strips){
    int i;
    for(i = this->size()-1; i >= 0 && str((*this)[i])->in(strips); --i);
    return this->substr(0, i+1);
  }
  str strip(str& strips){
    return this->strip_front(strips).strip_end(strips);
  }

  str join(str& s){
    return this->strip_end("/") + "/" + s.strip_front("/");
  }
};


void quit(const char* file, const char* fn){
  printf("Exiting from %s::%s\n", file, fn);
  exit(0);
}

str file2str(str& file){
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

void str2file(str& file, str& s){
  FILE* fp;
  fp = fopen(file.c_str(), "w");
  fprintf(fp, "%s\n", s.c_str());
  fclose(fp);
}

int call(str& cmd){
  int r;
  r = system(cmd);
  return (WIFEXITED(r) && !WEXITSTATUS(r)) ? 2 : 0;
}


#endif
