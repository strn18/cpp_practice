#include <iostream>
#define MAX 50

using namespace std;

int R, C;
int board[MAX][MAX];
int new_board[MAX][MAX];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void spread(int r, int c);
void cleaner(int up, int down);
void copy_board(int from[MAX][MAX], int to[MAX][MAX]);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T, up, down, total = 0;

  cin >> R >> C >> T;

  for(int i=0; i<R; i++)
    for(int j=0; j<C; j++)
      cin >> board[i][j];
  
  for(int i=2; i<R-2; i++){
    if(board[i][0] == -1){
      up = i;
      down = i+1;
      break;
    }
  }

  while(T--){
    copy_board(board, new_board);

    for(int i=0; i<R; i++)
      for(int j=0; j<C; j++)
        spread(i, j);
    
    copy_board(new_board, board);

    cleaner(up, down);

    copy_board(new_board, board);
  }

  for(int i=0; i<R; i++)
    for(int j=0; j<C; j++)
      if(board[i][j] > 0) total += board[i][j];
  
  cout << total;  

  return 0;
}

void spread(int r, int c){
  int val = board[r][c]/5;

  if(val == 0) return;

  for(int i=0; i<4; i++){
    int nr = r+dr[i];
    int nc = c+dc[i];

    if(nr<0 || R<=nr || nc<0 || C<=nc || board[nr][nc] == -1) continue;

    new_board[nr][nc] += val;
    new_board[r][c] -= val;
  }
}

void cleaner(int up, int down){
  new_board[up][1] = 0; // 위쪽 공기청정기
  for(int j=1; j<=C-2; j++)
    new_board[up][j+1] = board[up][j]; // →
  for(int i=up; i>=1; i--)
    new_board[i-1][C-1] = board[i][C-1]; // ↑
  for(int j=C-1; j>=1; j--)
    new_board[0][j-1] = board[0][j]; // ←
  for(int i=0; i<=up-2; i++)
    new_board[i+1][0] = board[i][0]; // ↓

  new_board[down][1] = 0; // 아래쪽 공기청정기
  for(int j=1; j<=C-2; j++)
    new_board[down][j+1] = board[down][j]; // →
  for(int i=down; i<=R-2; i++)
    new_board[i+1][C-1] = board[i][C-1]; // ↓
  for(int j=C-1; j>=1; j--)
    new_board[R-1][j-1] = board[R-1][j]; // ←
  for(int i=R-1; i>=down+2; i--)
    new_board[i-1][0] = board[i][0]; // ↑
}

void copy_board(int from[MAX][MAX], int to[MAX][MAX]){
  for(int i=0; i<R; i++)
    for(int j=0; j<C; j++)
      to[i][j] = from[i][j];
}

/*
그냥 빡구현 문제. 딱히 어려울 건 없고 그냥 1) 먼지 확산, 2) 공기청정기 작동. 이 두 개만 잘 구현해주면 됨.

먼지 확산은, 모든 먼지에서 한 번에 일어나기 때문에, 따로 2차원 배열(new_board)을 만들어서 거기에 변화값을 갱신했다. 걍 4방향 보면서, 
보드 밖이거나 공기청정기 부분이면 continue하고, 그렇지 않으면 먼지를 확산시켜서 그 값을 new_board에 더해주고 자신의 칸에서는 빼주면 됨.

공기청정기 작동은, 그냥 방향 별로 다 해주면 된다. cleaner 함수에 주석처리 해준 것처럼 방향 별로 따로따로 for문 써서 그냥 해주면 됨.
귀찮기만 하고 어렵진 않았다.
*/