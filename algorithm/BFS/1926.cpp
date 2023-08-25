#include <iostream>
#include <queue>
#define MAX 500

using namespace std;

int n, m;
int board[MAX][MAX];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int countSize(int r, int c); // (r, c)에서 bfs를 시작. 인접한 1 칸을 방문하여 2로 바꾸고 개수를 세어 리턴.

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int count = 0, maxSize = 0;

  cin >> n >> m;

  for(int i=0; i<n; i++)
    for(int j=0; j<m; j++)
      cin >> board[i][j];
  
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      if(board[i][j] == 1){
        ++count;
        maxSize = max(maxSize, countSize(i, j));
      }
    }
  }

  cout << count << '\n' << maxSize;

  return 0;
}

int countSize(int r, int c){
  queue<pair<int, int>> Q;
  int count = 0;

  Q.push({r, c});
  board[r][c] = 2;
  ++count;

  while(!Q.empty()){
    int curR = Q.front().first;
    int curC = Q.front().second;

    Q.pop();

    for(int i=0; i<4; i++){
      int nextR = curR + dr[i];
      int nextC = curC + dc[i];

      if(nextR < 0 || n <= nextR || nextC < 0 || m <= nextC || board[nextR][nextC] != 1) continue;

      Q.push({nextR, nextC});
      board[nextR][nextC] = 2;
      ++count;
    }
  }

  return count;
}

/*
그냥 기초 bfs/dfs 문제.
*/