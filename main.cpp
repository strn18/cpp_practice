#include <iostream>
#include <vector>
#define MAX 100

using namespace std;

bool board[MAX+1][MAX+1] = {false};
int dr[4] = {0, -1, 0, 1};
int dc[4] = {1, 0, -1, 0};

pair<int, int> makeDragonCurve(int r, int c, int d, int g);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, ans = 0;

  cin >> N;
  
  while(N--){
    int x, y, d, g;

    cin >> x >> y >> d >> g;

    makeDragonCurve(y, x, d, g);
  }

  for(int i=0; i<MAX; i++)
    for(int j=0; j<MAX; j++)
      if(board[i][j] && board[i][j+1] && board[i+1][j] && board[i+1][j+1]) ++ans;

  cout << ans;

  return 0;
}

pair<int, int> makeDragonCurve(int r, int c, int d, int g){
  board[r][c] = true;

  if(g == 0){
    int nextR = r + dr[d];
    int nextC = c + dc[d];

    board[nextR][nextC] = true;

    return {nextR, nextC};
  }

  pair<int, int> mid = makeDragonCurve(r, c, d, g-1);

  int endR = mid.first + (c - mid.second);
  int endC = mid.second + (mid.first - r);

  makeDragonCurve(endR, endC, (d+3)%4, g-1);

  return {endR, endC};
}