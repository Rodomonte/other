// 2048

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5
#define SLEEP 10
#define INF 2000000000

int a[8][8], b[4][8][8];

bool done(){
  int i,j;
  for(i = 0; i < N; ++i)
    for(j = 0; j < N; ++j)
      if(!a[i][j] || (i > 0 && a[i-1][j] == a[i][j]) ||
         (j > 0 && a[i][j-1] == a[i][j])) return false;
  return true;
}

void sleep(){
  int t0;
  t0 = clock();
  while(clock() - t0 < SLEEP);
}

bool shift(int k){
  bool r;
  int i,j,ii,jj;
  r = false;
  for(i = 0; i < N; ++i) for(j = 0; j < N; ++j) b[k][i][j] = a[i][j];
  if(!k){
    for(i = 0; i < N; ++i){
      for(j = 0; j < N; ++j){
        if(!b[k][i][j]) continue;
        ii = i, jj = j;
        while(ii > 0 && !b[k][ii-1][jj])
          b[k][ii-1][jj] = b[k][ii][jj], b[k][ii][jj] = 0, --ii, r = true;
        if(ii > 0 && b[k][ii-1][jj] == b[k][ii][jj])
          b[k][ii-1][jj] <<= 1, b[k][ii][jj] = 0, r = true;
      }
    }

  }else if(k == 1){
    for(j = N-1; j >= 0; --j){
      for(i = 0; i < N; ++i){
        if(!b[k][i][j]) continue;
        ii = i, jj = j;
        while(jj < N-1 && !b[k][ii][jj+1])
          b[k][ii][jj+1] = b[k][ii][jj], b[k][ii][jj] = 0, ++jj, r = true;
        if(jj < N-1 && b[k][ii][jj+1] == b[k][ii][jj])
          b[k][ii][jj+1] <<= 1, b[k][ii][jj] = 0, r = true;
      }
    }

  }else if(k == 2){
    for(i = N-1; i >= 0; --i){
      for(j = 0; j < N; ++j){
        if(!b[k][i][j]) continue;
        ii = i, jj = j;
        while(ii < N-1 && !b[k][ii+1][jj])
          b[k][ii+1][jj] = b[k][ii][jj], b[k][ii][jj] = 0, ++ii, r = true;
        if(ii < N-1 && b[k][ii+1][jj] == b[k][ii][jj])
          b[k][ii+1][jj] <<= 1, b[k][ii][jj] = 0, r = true;
      }
    }

  }else{
    for(j = 0; j < N; ++j){
      for(i = 0; i < N; ++i){
        if(!b[k][i][j]) continue;
        ii = i, jj = j;
        while(jj > 0 && !b[k][ii][jj-1])
          b[k][ii][jj-1] = b[k][ii][jj], b[k][ii][jj] = 0, --jj, r = true;
        if(jj > 0 && b[k][ii][jj-1] == b[k][ii][jj])
          b[k][ii][jj-1] <<= 1, b[k][ii][jj] = 0, r = true;
      }
    }
  }
  return r;
}

void move(){
  bool f;
  int i,j,k;
  
  
  printf("shift %d\n", k);
  for(i = 0; i < N; ++i) for(j = 0; j < N; ++j) a[i][j] = b[k][i][j];
  while(a[(i = rand()%N)][(j = rand()%N)]);
  a[i][j] = (rand()%2) ? 2 : 4;
}

void draw(){
  int i,j;
  printf("\n-");
  for(j = 0; j < N; ++j) printf("------");
  for(i = 0; i < N; ++i){
    printf("\n|");
    for(j = 0; j < N; ++j) printf("     |");
    printf("\n|");
    for(j = 0; j < N; ++j){
      if(a[i][j]) printf("%5d|", a[i][j]);
      else printf("     |");
    }
    printf("\n|");
    for(j = 0; j < N; ++j) printf("     |");
    printf("\n-");
    for(j = 0; j < N; ++j) printf("------");
  }
  printf("\n");
}

int main(int argc, char** argv){
  int i,j,t;
  for(i = 0; i < N; ++i) for(j = 0; j < N; ++j) a[i][j] = 0;
  i = rand() % N, j = rand() % N;
  a[i][j] = 2;
  while(a[i][j]) i = rand() % N, j = rand() % N;
  a[i][j] = 2;
  draw(), t = 1;
  while(!done()){
    printf("Turn %d:\n", t);
    sleep();
    move();
    draw();
    ++t;
  }
  return 0;
}
