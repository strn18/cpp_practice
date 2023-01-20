#include <iostream>
#include <queue>
#define MAX 100
// I renamed the repository.
using namespace std;

typedef struct{int r, c;} pos;

int N;
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void bfs(int board[][MAX], pos start);

int main(){
  char temp;
  int normal_count = 0, blind_count = 0;
  int normal_board[MAX][MAX], blind_board[MAX][MAX];

  scanf("%d", &N);

  getchar();
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      scanf("%c", &temp);
      normal_board[i][j] = temp;
      blind_board[i][j] = (temp == 'G' ? 'R' : temp);
    }
    getchar();
  }

  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      if(normal_board[i][j] != -1){
        bfs(normal_board, {i, j});
        normal_count++;
      }
    }
  }

  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      if(blind_board[i][j] != -1){
        bfs(blind_board, {i, j});
        blind_count++;
      }
    }
  }

  printf("%d %d", normal_count, blind_count);

  return 0;
}

void bfs(int board[][MAX], pos start){
  int district = board[start.r][start.c];
  board[start.r][start.c] = -1;

  queue<pos> Q;
  Q.push(start);

  while(!Q.empty()){
    pos cur = Q.front();
    Q.pop();

    for(int i=0; i<4; i++){
      pos next = {cur.r + dr[i], cur.c + dc[i]};
      if(0<=next.r && next.r<N && 0<=next.c && next.c<N && board[next.r][next.c] == district){
        board[next.r][next.c] = -1;
        Q.push(next);
      }
    }
  }
}