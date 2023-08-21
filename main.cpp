#include <iostream>
#include <cstdlib>
#define MAX 100

using namespace std;

int N, L;
int board[MAX][MAX];
bool stair[MAX][MAX] = {false};

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

bool checkHeight(int r, int c, int dir, int num, int h); // (r, c)의 상/하/좌/우에 있는 num개의 칸의 높이가 h이고 계단이 없다면 true.
void markStair(int r, int c, int dir, int num); // (r, c)의 상/하/좌/우에 있는 num개의 칸의 stair 값을 true로.
bool outOfBound(int r, int c);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int ans = 0;

  cin >> N >> L;

  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      cin >> board[i][j];

  for(int i=0; i<N; i++){ // 모든 행 확인
    bool isPassable = true;
    int prevHeight = board[i][0];

    for(int j=1; j<N; j++){
      if(board[i][j] == prevHeight) continue; // 높이 차가 0

      if(abs(board[i][j] - prevHeight) >= 2){ // 높이 차가 2 이상
        isPassable = false;
        break;
      }

      // 높이 차가 1
      if(prevHeight < board[i][j] && checkHeight(i, j, 2, L, prevHeight)){
        prevHeight = board[i][j];
        continue;
      }
      else if(prevHeight > board[i][j] && checkHeight(i, j-1, 3, L, board[i][j])){
        markStair(i, j-1, 3, L);
        prevHeight = board[i][j];
        continue;
      }
      else{
        isPassable = false;
        break;
      }
    }

    if(isPassable) ++ans;
  }

  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      stair[i][j] = false;

  for(int j=0; j<N; j++){ // 모든 열 확인
    bool isPassable = true;
    int prevHeight = board[0][j];

    for(int i=1; i<N; i++){
      if(board[i][j] == prevHeight) continue; // 높이 차가 0

      if(abs(board[i][j] - prevHeight) >= 2){ // 높이 차가 2 이상
        isPassable = false;
        break;
      }

      // 높이 차가 1
      if(prevHeight < board[i][j] && checkHeight(i, j, 0, L, prevHeight)){
        prevHeight = board[i][j];
        continue;
      }
      else if(prevHeight > board[i][j] && checkHeight(i-1, j, 1, L, board[i][j])){
        markStair(i-1, j, 1, L);
        prevHeight = board[i][j];
        continue;
      }
      else{
        isPassable = false;
        break;
      }
    }

    if(isPassable) ++ans;
  }

  cout << ans;

  return 0;
}

bool checkHeight(int r, int c, int dir, int num, int h){
  if(outOfBound(r + dr[dir]*num, c + dc[dir]*num)) return false;

  for(int i=1; i<=num; i++){
    int nr = r + dr[dir]*i;
    int nc = c + dc[dir]*i;

    if(stair[nr][nc] || board[nr][nc] != h) return false;
  }

  return true;
}

void markStair(int r, int c, int dir, int num){
  for(int i=1; i<=num; i++)
    stair[r + dr[dir]*i][c + dc[dir]*i] = true;
}

bool outOfBound(int r, int c){
  if(r<0 || N<=r || c<0 || N<=c) return true;
  else return false;
}