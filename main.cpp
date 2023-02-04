#include <iostream>
#include <cstring>
#define MAX 300

using namespace std;

int N, M;
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
int board[MAX][MAX];
int next_board[MAX][MAX];
bool visited[MAX][MAX];

int check(void);
void dfs(int r, int c);
void melt(int r, int c);
void copy_board(int from[][MAX], int to[][MAX]);

int main(){
  int pieces, years = 0;

  scanf("%d %d", &N, &M);

  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      scanf("%d", &board[i][j]);

  while(true){
    pieces = check();
    if(pieces != 1) break;

    years++;
    copy_board(board, next_board);

    for(int r=0; r<N; r++)
      for(int c=0; c<M; c++)
        if(board[r][c] > 0)
          melt(r, c);

    copy_board(next_board, board);
  }

  if(pieces == 0)
    printf("0");
  else
    printf("%d", years);

  return 0;
}

int check(void){
  int count = 0;
  memset(visited, false, MAX*MAX*sizeof(bool));

  for(int r=0; r<N; r++){
    for(int c=0; c<M; c++){
      if(!visited[r][c] && board[r][c] > 0){
        dfs(r, c);
        count++;
      }
    }
  }

  return count;
}

void dfs(int r, int c){
  visited[r][c] = true;

  for(int i=0; i<4; i++)
    if(!visited[r+dr[i]][c+dc[i]] && board[r+dr[i]][c+dc[i]] > 0)
      dfs(r+dr[i], c+dc[i]);
}

void melt(int r, int c){
  for(int i=0; i<4; i++)
    if(board[r+dr[i]][c+dc[i]] == 0)
      next_board[r][c]--;
  next_board[r][c] = max(0, next_board[r][c]);
}

void copy_board(int from[][MAX], int to[][MAX]){
  for(int r=0; r<N; r++)
    for(int c=0; c<M; c++)
      to[r][c] = from[r][c];
}