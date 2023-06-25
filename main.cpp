#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 10

using namespace std;

int N, M;
int board[MAX][MAX]; // -2: 바다, -1: 섬(그룹화 전), else: 섬(그룹화 후)

int parent[6];

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void dfs(int r, int c, int num);
int find_root(int x);
bool union_root(int x, int y);
bool range_out(int r, int c);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int island = 0, ans = 0;
  vector<pair<int, pair<int, int>>> edge;

  cin >> N >> M;

  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      cin >> board[i][j];
      board[i][j] -= 2;
    }
  }
  
  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      if(board[i][j] == -1)
        dfs(i, j, island++);
  
  for(int i=0; i<island; i++)
    parent[i] = i;

  for(int r=0; r<N; r++){
    for(int c=0; c<M; c++){
      if(board[r][c] == -2) continue;

      for(int i=0; i<4; i++){
        for(int j=1; true; j++){
          int nr = r + (dr[i]*j);
          int nc = c + (dc[i]*j);

          if(range_out(nr, nc)) break;

          if(board[nr][nc] == -2) continue;
          if(board[nr][nc] == board[r][c]) break;

          if(j > 2) edge.push_back({j-1, {board[r][c], board[nr][nc]}});

          break;
        }
      }
    }
  }

  sort(edge.begin(), edge.end());

  for(int i=0; i<edge.size(); i++){
    int d = edge[i].first;
    int a = edge[i].second.first;
    int b = edge[i].second.second;

    if(union_root(a, b)){
      ans += d;
      union_root(a, b);
      
      if(--island == 1) break;
    }
  }

  cout << (island == 1 ? ans : -1);

  return 0;
}

void dfs(int r, int c, int num){
  board[r][c] = num;

  for(int i=0; i<4; i++){
    int nr = r+dr[i];
    int nc = c+dc[i];

    if(range_out(nr, nc) || board[nr][nc] != -1) continue;

    dfs(nr, nc, num);
  }
}

int find_root(int x){
  if(parent[x] == x) return x;

  return parent[x] = find_root(parent[x]);
}

bool union_root(int x, int y){
  int rx = find_root(x);
  int ry = find_root(y);

  if(rx == ry) return false;

  parent[rx] = ry;

  return true;
}

bool range_out(int r, int c){
  if(r<0 || N<=r || c<0 || M<=c) return true;
  return false;
}