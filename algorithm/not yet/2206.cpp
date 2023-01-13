/*
#include <iostream>
#include <queue>
#define MAX 1000

using namespace std;

int map[MAX][MAX]; // 맵에 0 또는 1 기록
int visited[2][MAX][MAX] = {0}; // visited[n][i][j]는 (i, j) 방문 여부이다. 
// 이 때 n이 1이면 벽을 부순 상태에서, 0이면 아직 안 부순 상태에서의 방문 여부를 의미한다.
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

typedef struct{int breaked, r, c;}pos; // breaked는 현재 벽을 부순 상태일 때 1임.
queue<pos> pos_q;

int N, M, count=1;

void bfs(void);

int main(){
  char temp;
  
  scanf("%d %d", &N, &M);
  getchar();
  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      scanf("%c", &temp);
      map[i][j] = temp-'0';
    }
    getchar();
  }
  pos_q.push({0, 0, 0}); // (0, 0)칸에서 벽을 안 부순 상태로 시작
  visited[0][0][0] = 1; // 방문 표시
  
  if(N!=1 || M!=1) // N, M이 1이면 탐색 필요 x
    bfs();

  printf("%d", count);
  
  return 0;
}

void bfs(void){
  while(!pos_q.empty()){
    int n = pos_q.size(); // 현재 count에서의 움직임들(n개)을 탐색한다.
    count++;
    for(int i=0; i<n; i++){
      pos cur = pos_q.front();
      pos_q.pop();      

      for(int j=0; j<4; j++){
        pos move = {cur.breaked, cur.r+dr[j], cur.c+dc[j]}; // 상하좌우 움직임
        if(!(0<=move.r&&move.r<N && 0<=move.c&&move.c<M)) continue; // 범위 체크
        
        // 1. 움직일 칸에 벽이 없고, 현재 breaked 상태에서 방문 안 한 경우
        if(map[move.r][move.c]==0 && !visited[move.breaked][move.r][move.c]){
          if(move.r==N-1 && move.c==M-1) return; // 마지막 칸이면 리턴
          pos_q.push({move.breaked, move.r, move.c}); // breaked 상태는 그대로 유지
          visited[move.breaked][move.r][move.c]=1; // 현재 breaked 상태로 방문 체크
        }
          
        // 2. 움직일 칸에 벽이 있고, 뚫을 수 있을 때
        else if(map[move.r][move.c]==1 && !move.breaked){
          if(!visited[1][move.r][move.c]){ // 이때 해당 칸을 방문 안 한 상태라면
            if(move.r==N-1 && move.c==M-1) return; // 마지막 칸이면 리턴
            pos_q.push({1, move.r, move.c}); // breaked 상태는 1로 바뀐다
            visited[1][move.r][move.c]=1; // 벽을 부순 상태로 움직일 칸 방문 체크
          }
        }
      }      
    }
  }
  count = -1; // 만약 더 이상 움직임이 없을 경우 벽에 막힌 것
  return;
}

큰 틀에서는 차이가 없으나 세부적인 부분에서 조건 처리가 필요했던 bfs 문제. 상하좌우 4가지 
경우를 탐색하는 것은 기존 최단거리 bfs 문제와 비슷하나, 벽을 최대 1번까지 부술 수 있다는 
조건 때문에 좀 복잡했다. 처음에는 조건문을 크게 "현재 이미 벽을 부순 상태인지 아닌지"로 잡고 
그 안에 네 방향 도는 for문을 넣은 뒤 이리저리 복잡하게 코드를 짰는데, 맞긴 했으나 조건문 
부분이 너무 길어졌다. 그래서 이후 네 방향 도는 for문을 먼저 넣고, 그 안에 조건문을 크게 
"움직일 칸에 벽이 있는지 없는지"로 잡으면서 적당히 코드를 줄여보았다. 
bfs 문제에서 나는 주로 count 같은 변수를 선언하고 while문을 돌 때마다 count++을 해주는 식으로 코드를 짜는데, 다른 사람들 코드를 보면 주로 visited 배열에 해당 칸까지 갈 때 필요한 횟수를 직접 기록하는 식으로 코드를 짜더라. 뭐가 더 좋은지는 모르겠네
*/