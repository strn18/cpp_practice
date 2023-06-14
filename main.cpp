#include <iostream>
#include <string>
#define MAX 10

using namespace std;

typedef struct {int r, c;} pos;

int N, M, ans = 11;
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};

void copy_board(string from[MAX], string to[MAX]);
void move(int dir, string board[MAX], pos red, pos blue, int count);
pos move_bead(int dir, string board[MAX], pos bead);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string board[MAX];
  pos red, blue;

  cin >> N >> M;

  for(int i=0; i<N; i++)
    cin >> board[i];
  
  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      if(board[i][j] == 'R') red = {i, j};
      else if(board[i][j] == 'B') blue = {i, j};
    }
  }
  
  for(int i=0; i<4; i++)
    move(i, board, red, blue, 1);
  
  cout << (ans == 11 ? -1 : ans);

  return 0;
}

void copy_board(string from[MAX], string to[MAX]){
  for(int i=0; i<N; i++)
    to[i] = from[i];
}

void move(int dir, string board[MAX], pos red, pos blue, int count){
  bool red_first = true;
  string next[MAX];

  copy_board(board, next);

  if(dir == 0 && blue.r < red.r) red_first = false;
  else if(dir == 1 && blue.c < red.c) red_first = false;
  else if(dir == 2 && red.r < blue.r) red_first = false;
  else if(dir == 3 && red.c < blue.c) red_first = false;

  if(red_first){
    red = move_bead(dir, next, red);
    blue = move_bead(dir, next, blue);
  }
  else{
    blue = move_bead(dir, next, blue);
    red = move_bead(dir, next, red);
  }

  if(next[blue.r][blue.c] == 'O') return;

  if(next[red.r][red.c] == 'O'){
    ans = min(ans, count);
    return;
  }

  if(count == 10) return;

  for(int i=0; i<4; i++){
    if(i == dir || (i+2)%4 == dir) continue;
    move(i, next, red, blue, count+1);
  }
}

pos move_bead(int dir, string board[MAX], pos bead){
  while(true){
    int nr = bead.r+dr[dir];
    int nc = bead.c+dc[dir];

    if(board[nr][nc] == '.'){
      board[nr][nc] = board[bead.r][bead.c];
      board[bead.r][bead.c] = '.';
      bead = {nr, nc};
    }
    else if(board[nr][nc] == 'O'){
      board[bead.r][bead.c] = '.';
      return {nr, nc};
    }
    else return bead;
  }
}