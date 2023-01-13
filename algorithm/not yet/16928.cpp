/*
#include <iostream>
#include <queue>
#define MAX 100

using namespace std;

int board[MAX+1];
int visited[MAX+1];
int count=0;
queue<int> pos_q;

void bfs(void);

int main(){
  int N, M, x, y, u, v;
  
  for(int i=0; i<=MAX; i++){
    board[i] = i;
    visited[i] = 0;
  }
  
  scanf("%d %d", &N, &M);
  for(int i=0; i<N; i++){
    scanf("%d %d", &x, &y);
    board[x] = y;
  }
  for(int j=0; j<M; j++){
    scanf("%d %d", &u, &v);
    board[u] = v;
  }

  pos_q.push(1);
  bfs();

  printf("%d", count);
  
  return 0;
}

void bfs(void){
  while(1){
    int n = pos_q.size();
    count++;
    for(int i=0; i<n; i++){
      int cur = pos_q.front();
      pos_q.pop();
      for(int j=1; j<=6; j++){
        if(board[cur+j]==MAX)
          return;
        if(board[cur+j]<MAX && visited[board[cur+j]]==0){
          pos_q.push(board[cur+j]);
          visited[board[cur+j]] = 1;
        }
      }
    }
  }
}

이것도 별로 안 어려웠던 bfs 변형 문제. 보드판은 1부터 100까지니까 int형 1차원 배열 board로 만들어두고, board의 값은 i번째 칸에 사다리 or 뱀이 있어서 j칸으로 가게 된다면 board[i]=j, 없다면 board[i]=i로 설정해두었다. 이후 bfs로 큐를 돌면서 주사위 던져서 나오는 6가지 경우를 각각 반복하고 결과값은 큐에 다시 넣는다. 
*/