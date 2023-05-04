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

/*
오랜만에 푼 dfs 문제(bfs로도 가능). 다른 건 어렵지 않고, 문제에서 주어지는 좌표는 점의 좌표인데, 칸의 좌표랑은 다르기 때문에 그거에만 유의하면
된다. 가령, 0 2 4 4 가 주어졌다면, 칸의 좌표를 쓰는 board에서 02 03 12 13 22 23 32 33 이 좌표가 직사각형에 해당된다. 즉, r1 c1 r2 c2가 
주어질 때, 행은 [r1, r2), 열은 [c1, c2)에 해당하는 좌표들이 직사각형이 해당되니까, 걔네들을 찾아서 board값을 바꿔주면 된다(방문 처리, 32~34행).

그리고 마지막에, 영역의 개수 뿐만 아니라 각 영역의 넓이를 오름차순으로 정렬해 출력해야 함.
*/