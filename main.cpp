#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 100

using namespace std;

int R, C;
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
bool board[MAX][MAX] = {false};

int dfs(int r, int c);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int M, N, K;
  int total = 0;
  vector<int> area;

  cin >> M >> N >> K;

  R = N; C = M;

  for(int i=0; i<K; i++){
    int r1, c1, r2, c2;

    cin >> r1 >> c1 >> r2 >> c2;

    for(int r=r1; r<r2; r++)
      for(int c=c1; c<c2; c++)
        board[r][c] = true;
  }

  for(int i=0; i<R; i++){
    for(int j=0; j<C; j++){
      if(!board[i][j]){
        total++;
        area.push_back(dfs(i, j));
      }
    }
  }

  cout << total << '\n';

  sort(area.begin(), area.end());
  for(int i=0; i<area.size(); i++)
    cout << area[i] << ' ';

  return 0;
}

int dfs(int r, int c){
  int count = 1;
  board[r][c] = true;

  for(int i=0; i<4; i++){
    int nr = r+dr[i], nc = c+dc[i];

    if(0<=nr && nr<R && 0<=nc && nc<C)
      if(!board[nr][nc])
        count += dfs(nr, nc);
  }

  return count;
}