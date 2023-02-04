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

/*
좀 복잡했으나 크게 어렵지 않았던 dfs 문제. 

빙산에 대해, 매 턴마다 두 가지 행동을 취해주면 된다.
1. 빙산이 몇 덩어리인지 센다. 두 덩어리 이상으로 쪼개졌거나, 다 녹아서 덩어리가 없다면 break.
2. 빙산의 각 칸을 녹인다. 인접한 네 칸 중 물(board 값이 0)이 있는 칸 만큼 녹이면 된다.

우선, 1번에서 break된 이후에는, 두 덩어리 이상으로 쪼개졌으면 그동안 지난 시간을 출력하면 되고, 두 덩어리 이상으로 안 쪼개지고 바로 다 녹았다면
0을 출력해준다. 

1번은 dfs를 통해 구현했다. 모든 칸을 돌면서, 빙산인 칸을 찾았으면, 그 칸을 시작으로 인접한 빙산 칸들로 뻗어나가면서 dfs를 친다. 이때 방문하는
칸들을 체크해준다. 이런 식으로 해서, 방문한 칸은 dfs를 치지 않는 식으로 짜면, dfs를 시작하는 칸의 개수 == 빙산 덩어리의 개수가 된다(59행).

2번은 그냥 간단하게 모든 칸을 돌면서, 빙산인 칸을 찾으면, 그 주위 네 칸을 보고 물이 있는 만큼 빙산인 칸의 board 값을 줄여주면 된다. 근데 이때,
칸이 0 1 2 0 이렇게 있다고 치자. 이 빙산은 다음 턴에 0 0 1 0 이 되어야 한다(값이 1과 2인 칸 모두 주위에 물이 하나 있으므로, 1씩 감소).
근데, 1인 칸을 먼저 0으로 줄여버리고 2인 칸에 오게 되면, 주위에 물이 두 개 있는 것으로 보고 값을 0으로 줄여버리게 된다.
이걸 방지하기 위해, 2번을 실행할 때마다 next_board 배열을 이용하여, 어떠한 빙산 칸 근처에 물인 칸이 몇 개 있는지는 board 배열의 값을 참고하고,
이를 통해 줄어든 빙산 칸의 값은 next_board에 넣어준다. 이게 다 끝나면, board에 다시 next_board를 넣어주면 된다.

구현할 게 많았지만 어렵지는 않았는데, 다른 풀이 보니까 1번을 bfs로 구현한 풀이도 있었다. 어차피 붙어있는 빙산 칸으로 뻗어나가는 탐색만 하면
되니까, dfs든 bfs든 상관 없을듯.
*/