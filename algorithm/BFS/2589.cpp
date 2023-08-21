#include <iostream>
#include <string>
#include <queue>
#define MAX 50

using namespace std;

int N, M, ans = 0;
int board[MAX][MAX];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void bfs(int r, int c, int val);
bool outOfBound(int r, int c);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N >> M;

  for(int i=0; i<N; i++){
    string str;

    cin >> str;

    for(int j=0; j<M; j++)
      board[i][j] = (str[j] == 'W' ? -1 : 0);
  }

  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      if(board[i][j] >= 0) bfs(i, j, board[i][j]);
  
  cout << ans;

  return 0;
}

void bfs(int r, int c, int val){
  queue<pair<pair<int, int>, int>> bfsQ;

  bfsQ.push({{r, c}, 0});
  board[r][c] = val + 1;

  while(true){
    pair<pair<int, int>, int> cur = bfsQ.front();
    bfsQ.pop();

    for(int i=0; i<4; i++){
      int nr = cur.first.first + dr[i];
      int nc = cur.first.second + dc[i];

      if(outOfBound(nr, nc) || board[nr][nc] != val) continue;

      bfsQ.push({{nr, nc}, cur.second + 1});
      board[nr][nc] = val + 1;
    }

    if(bfsQ.empty()){
      ans = max(ans, cur.second);
      return;
    }
  }
}

bool outOfBound(int r, int c){
  if(r<0 || N<=r || c<0 || M<=c) return true;
  else return false;
}

/*
괜히 어렵게 생각한 bfs 문제. 처음에는 이렇게 생각했다(첫번째 제출).
1) 아무 육지(L)를 발견하면 bfs를 친다.
2) 그 칸에서 가장 멀리 떨어진 육지 칸을 찾는다.
3) 그 육지 칸에서 다시 bfs를 친다. 
4) 거기에서 가장 멀리 떨어진 거리가 해당 대륙(육지가 연결된 것들)에서 가장 멀리 떨어진 두 칸의 거리이다. 이걸 이용해서 ans를 갱신.

이렇게 하니깐 테케 대부분은 맞는데, 2)에서 가장 멀리 떨어진 육지 칸이 여러 개일 때 틀리는 경우가 발생한다. 가령, 
WLLLL
LLLLW
이런 형태라면, (0, 1)에서 1)을 시작하게 된다. 근데 (0, 4)와 (1, 3)과의 거리가 모두 3으로 동일하다. 이때, (0, 4)에서 3)을 시작해야 
답을 구할 수 있는데((0, 4)와 (1, 0)이 최대 거리), (1, 3)에서 시작하게 되면 틀리게 된다.

그래서, 누가 봐도 너무 복잡해서 답은 아닌 것 같지만, 2)에 해당하는 여러 개에서 모두 3)을 시작해보는 방식으로도 코드를 짰는데(세번째 제출) 
틀렸다.

그래서 그냥 단순하게, 브루트포스 느낌으로, 애초에 모든 육지 칸에서 3)을 쳐보기로 했다. 그랬더니 맞았음.
*/