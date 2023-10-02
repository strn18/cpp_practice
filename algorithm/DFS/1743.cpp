#include <iostream>
#define MAX 1000

using namespace std;

bool waste[MAX+2][MAX+2] = {false};
bool visited[MAX+2][MAX+2] = {false};
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int getSize(int r, int c);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, K, maxSize = 0;

  cin >> N >> M >> K;

  while(K--){
    int r, c;

    cin >> r >> c;

    waste[r][c] = true;
  }

  for(int i=1; i<=N; i++){
    for(int j=1; j<=M; j++){
      if(waste[i][j] && !visited[i][j])
        maxSize = max(maxSize, getSize(i, j));
    }
  }

  cout << maxSize;

  return 0;
}

int getSize(int r, int c){
  int count = 1;
  
  visited[r][c] = true;

  for(int i=0; i<4; i++){
    int nr = r + dr[i];
    int nc = c + dc[i];

    if(!waste[nr][nc] || visited[nr][nc]) continue;

    count += getSize(nr, nc);
  }

  return count;
}

/*
걍 흔한 dfs 문제. 근데 범위 초과하는지 체크하는 부분(50행에 넣어야겠지) 안 넣고 제출했는데 맞았다. 그래도 걍 완벽하게 맞기 위해서, 
범위 초과 체크하는 대신에 그냥 waste 배열을 상하좌우로 한 칸씩 넉넉하게 만들어서 보완해서 냈음. 이러면 범위가 초과하는 칸의 경우, 
waste 값이 반드시 false이기에 50행에서 무조건 걸린다. 
*/