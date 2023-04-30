#include <iostream>
#include <queue>
#define MAX 100

using namespace std;

int N, board[MAX][MAX];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int bfs(int h);

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

  for(int i=low-1; i<=high; i++)
    ans = max(ans, bfs(i));
  
  cout << ans;

  return 0;
}

int bfs(int h){
  int count = 0;
  bool visited[MAX][MAX] = {false};

  queue<pair<int, int>> Q;

  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      if(board[i][j]>h && !visited[i][j]){
        Q.push({i, j});
        visited[i][j] = true;
        count++;

        while(!Q.empty()){
          int cur_r = Q.front().first;
          int cur_c = Q.front().second;
          Q.pop();

          for(int k=0; k<4; k++){
            int next_r = cur_r+dr[k];
            int next_c = cur_c+dc[k];
            if(0<=next_r && next_r<N && 0<=next_c && next_c<N){
              if(board[next_r][next_c]>h && !visited[next_r][next_c]){
                Q.push({next_r, next_c});
                visited[next_r][next_c] = true;
              }
            }
          }
        }
      }
    }
  }

  return count;
}

/*
bfs로 풀었는데 걍 dfs로 푸는 게 더 간결할듯..
*/