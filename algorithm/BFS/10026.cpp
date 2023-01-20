#include <iostream>
#include <queue>
#define MAX 100

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

/*
어렵지 않았던 bfs 문제. 입력받은 보드에 대해서, 같은 색끼리 탐색하도록 bfs를 짜주면 된다. 그러면, 어떠한 칸에서 bfs를 시작하면 그 칸과 연결이
되어있고 색이 같은 칸들을 bfs로 탐색하게 되는데, 이때 그 칸들의 값을 -1로 바꿔준다. 이것을 보드의 모든 칸을 돌면서, 해당 칸이 -1이 아닐 때
실행해주면 된다. 이렇게 하면 bfs를 실행한 횟수 = 구역의 개수가 된다. 이때, 적록색약인 사람의 보드는 G를 R로 바꿔놓고 시작해야 한다.
bfs 함수에서, 탐색을 시작하는 칸은 start이고, 해당 칸의 색(값)은 district이다. 그 칸부터 시작하여 bfs를 돌리며, 연결되어있고 색이 district인
칸으로 탐색을 뻗어나가면서 그 칸들의 값을 -1로 바꿔주면 됨.
*/