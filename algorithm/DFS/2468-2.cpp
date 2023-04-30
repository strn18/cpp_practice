#include <iostream>
#define MAX 100

using namespace std;

int N, board[MAX][MAX];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int solve(int h);
void dfs(bool visited[MAX][MAX], int r, int c, int h);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int high = 0, low = 101, ans = 0;

  cin >> N;

  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      cin >> board[i][j];
      high = max(high, board[i][j]);
      low = min(low, board[i][j]);
    }
  }

  for(int h=low-1; h<=high; h++)
    ans = max(ans, solve(h));
  
  cout << ans;

  return 0;
}

int solve(int h){
  bool visited[MAX][MAX] = {false};
  int count = 0;

  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      if(board[i][j]>h && !visited[i][j]){
        count++;
        dfs(visited, i, j, h);
      }
    }
  }

  return count;
}

void dfs(bool visited[MAX][MAX], int r, int c, int h){
  visited[r][c] = true;

  for(int i=0; i<4; i++){
    int nr = r+dr[i];
    int nc = c+dc[i];

    if(0<=nr && nr<N && 0<=nc && nc<N)
      if(board[nr][nc]>h && !visited[nr][nc])
        dfs(visited, nr, nc, h);
  }
}

/*
2468을 dfs로도 한 번 풀어봄. 재귀 쓰니까 좀 간결해지긴 함.
*/