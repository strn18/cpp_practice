/*
#include <iostream>
#include <queue>
#include <string.h>
#define MAX 300

using namespace std;

typedef struct{int r, c;}pos;
pos knt_first, knt_target;
queue<pos> knt_q;

int visited[MAX][MAX];
int count, side;

int dr[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
int dc[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

void bfs(void);

int main(){
  int T;
  scanf("%d", &T);

  for(int i=0; i<T; i++){
    memset(visited, 0, MAX*MAX*sizeof(int));
    count = 0;
    knt_q = queue<pos>();
    
    int r1, c1, r2, c2;
    scanf("%d", &side);
    scanf("%d %d", &r1, &c1);
    knt_first = {r1, c1};
    scanf("%d %d", &r2, &c2);
    knt_target = {r2, c2};

    if(r1!=r2 || c1!=c2){
      knt_q.push(knt_first);
      bfs();
    }
    printf("%d\n", count);
  }
    
  return 0;
}

void bfs(void){
  while(1){
    int n = knt_q.size();
    count++;
    
    for(int i=0; i<n; i++){
      pos cur = knt_q.front();
      knt_q.pop();
      
      for(int j=0; j<8; j++){
        pos move = {cur.r+dr[j], cur.c+dc[j]};
        if(0<=move.r && move.r<side && 0<=move.c && move.c<side){
          if(visited[move.r][move.c]==0){
            if(move.r==knt_target.r && move.c==knt_target.c)
              return;
            knt_q.push({move.r, move.c});
            visited[move.r][move.c] = 1;
          }
        }
      }
    }
  }
}

별로 안 어려운 bfs 변형 문제. 움직일 수 있는 경우의 수가 2차원 좌표에서 8가지라는 것만 유의하면 어렵지 않게 풀 수 있었다.
*/