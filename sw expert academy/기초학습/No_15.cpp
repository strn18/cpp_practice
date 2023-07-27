// 프로세서 연결하기(5. 그래프)
#include <iostream>
#include <vector>
#define MAX 12

using namespace std;

int N, max_connect, min_len;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int board[MAX][MAX];

vector<pair<int, int>> core;

void dfs(int depth, int connect, int len);
bool check_dir(int r, int c, int d);
int mark_dir(int r, int c, int d);
void del_dir(int r, int c, int d);
bool out_of_bound(int r, int c);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  for(int t=1; t<=T; t++){
    max_connect = 0, min_len = MAX*MAX;
    core = vector<pair<int, int>>();

    cin >> N;

    for(int i=0; i<N; i++){
      for(int j=0; j<N; j++){
        cin >> board[i][j];

        if(board[i][j] == 1) core.push_back({i, j});
      }
    }

    dfs(0, 0, 0);

    cout << '#' << t << ' ' << min_len << '\n';
  }

  return 0;
}

void dfs(int depth, int connect, int len){
  if(depth == core.size()){
    if(connect > max_connect){
      max_connect = connect;
      min_len = len;
    }
    else if(connect == max_connect)
      min_len = min(min_len, len);

    return;
  }

  if(connect + core.size()-depth < max_connect) return;

  int r = core[depth].first, c = core[depth].second;

  for(int d=0; d<4; d++){
    if(check_dir(r, c, d)){
      dfs(depth + 1, connect + 1, len + mark_dir(r, c, d));
      del_dir(r, c, d);
    }
    else dfs(depth + 1, connect, len);
  }
}

bool check_dir(int r, int c, int d){
  for(int i=1; true; i++){
    int nr = r+(dr[d]*i);
    int nc = c+(dc[d]*i);

    if(out_of_bound(nr, nc)) return true;
    if(board[nr][nc]) return false;
  }
}

int mark_dir(int r, int c, int d){
  for(int i=1; true; i++){
    int nr = r+(dr[d]*i);
    int nc = c+(dc[d]*i);

    if(out_of_bound(nr, nc)) return i-1;
    board[nr][nc] = 2;
  }
}

void del_dir(int r, int c, int d){
  for(int i=1; true; i++){
    int nr = r+(dr[d]*i);
    int nc = c+(dc[d]*i);

    if(out_of_bound(nr, nc)) return;
    board[nr][nc] = 0;
  }
}

bool out_of_bound(int r, int c){
  if(r<0 || N<=r || c<0 || N<=c) return true;
  else return false;
}

/*
각 코어들을 4방향으로 다 dfs 치면서, 가장 많은 코어를 연결하였을 때 가장 적은 전선 길이의 합을 구하면 된다.

다 풀어놓고 시간초과가 났었는데, 아니 여기서 어떻게 더 시간복잡도를 줄일 수가 없는데? 싶어서 뒤1지게 고민했는데, 65행에 가지치기 부분 하나 
넣으니깐 시간초과 안 나고 맞았음.. 지금까지의 연결된 코어의 개수(connect)+앞으로 볼(남아있는) 코어의 개수(core.size()-depth) 의 값이 
이미 구해놓은 max_connect보다 작다면, 더 이상 볼 가치가 없으므로 백트래킹하는 코드이다. 설마 이거 넣는다고 시간이 크게 줄어들까? 했는데 설마가 
맞았음. 진짜 어이없다
*/