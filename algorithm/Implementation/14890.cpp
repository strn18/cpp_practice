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
      if(board[i][j] == prevHeight) continue; // 이전 칸과 높이 차가 0

      if(abs(board[i][j] - prevHeight) >= 2){ // 이전 칸과 높이 차가 2 이상
        isPassable = false;
        break;
      }

      // 이전 칸과 높이 차가 1
      if(prevHeight < board[i][j] && checkHeight(i, j, 2, L, prevHeight)){ // 이번 칸 좌측의 L개의 칸의 높이가 모두 prevHeight라면
        prevHeight = board[i][j]; // 경사로를 놓을 수 있다. 왼쪽에 놓았으므로 stair 표시 굳이 할 필요 없음(놓은 칸을 돌아볼 일이 없다).
        continue;
      }
      else if(prevHeight > board[i][j] && checkHeight(i, j-1, 3, L, board[i][j])){ // 이번 칸 포함, 우측의 L개의 칸 높이가 board[i][j]라면
        markStair(i, j-1, 3, L); // 경사로를 놓을 수 있다. 오른쪽에 놓았으므로 stair 표시 해야 함.
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

  for(int j=0; j<N; j++){ // 모든 열 확인(이하 내용 같다)
    bool isPassable = true;
    int prevHeight = board[0][j];

    for(int i=1; i<N; i++){
      if(board[i][j] == prevHeight) continue;

      if(abs(board[i][j] - prevHeight) >= 2){
        isPassable = false;
        break;
      }

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
  if(outOfBound(r + dr[dir]*num, c + dc[dir]*num)) return false; // 끝칸만 보고, 확인할 칸들이 범위를 벗어나는지 확인.

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

/*
ㅈㄴ 이상한 문제; 경사로 겹치면 안 된다면서, 행으로 놓을 때랑 열로 놓을 때는 겹쳐도 됨 ㅋㅋ 뭔 소리나면,
3333
3223
3223
3333
이렇게 높이가 주어지고, L=2라고 하자. 그러면, 2행과 3행에 가로로 2칸짜리 경사로를 놓을 수 있다.
근데, 2열과 3열에 세로로 2칸짜리 경사로도 놓을 수 있음.

즉, 저렇게 겹치는 건 가능하고
32223
이 상황에서, 2칸짜리 경사로를 가로로 2개 겹치게는 못 놓는다.

이거 때문에 문제가 훨씬 쉬워진듯. 그냥 모든 행 돌면서 확인하고, 그 다음엔 모든 열 돌면서 확인하면 된다.

*/