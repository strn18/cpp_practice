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

/*
MST, DFS(BFS), 브루트 포스가 다 섞여있는 문제. 크게 세 부분으로 나눌 수 있음.

1) 입력받은 board에 대해서, 같은 섬인 점들은 board 값이 같도록 해주기. 바다인 칸은 board 값이 -2, 아직 그룹화 되기 전의 땅은 -1,
그룹화가 되었다면 0 이상의 정수를 board 값으로 가짐. 같은 섬에 속한 두 점 (r1, c1), (r2, c2)가 있다면, board[r1][c1] == board[r2][c2] 이다.

2) board의 모든 점을 돌면서, 상하좌우로 뻗어나가면서 다른 섬에 속한 점을 발견했을 경우(두 점의 board 값이 다름), 그 두 점을 잇는 간선의
정보를 edge에 넣는다. 간선의 정보는 {거리, {한 점의 섬 index, 다른 점의 섬 index}}로 이루어짐. 이후 다 끝났다면 edge를 간선의 길이(거리) 기준
오름차순 정렬(크루스칼 쓰기 위함).

3) edge를 하나하나 꺼내면서, edge 정보에서 두 점의 섬 index를 각각 a와 b라고 할 때, find_root(a) != find_root(b)라면 둘을 union_root 해주고
ans += 간선의 길이를 해준다. 이거를 island(섬의 개수)-1번 해주었다면 끝이니까 break. 모든 edge를 다 돌았는데, 저거를 island-1번 못 했다면 
모든 섬을 다 잇지 못했으므로 -1 출력. 아니면 ans 출력.

과정 1)을 하기 위해서 dfs를 썼음. 모든 점을 돌면서, 땅인데 아직 그룹화 되기 전이라면(board 값이 -1), 걔를 시작으로 dfs를 치면서 인접한 점들을
같은 섬으로 그룹화 해준다. 걔네들의 board 값으로 island 값을 넣어주고, 섬이 하나 추가되었으므로 island++를 해줌(40행). 이게 끝나면, board에서
-2는 바다인 칸, 0은 섬 index가 0인 땅들, 1인 섬 index가 1인 땅들... 로 바뀌게 됨.

과정 2)에서는 이제 한 섬과 다른 섬을 잇는 모든 간선을 찾아 edge에 넣는다. 이를 위해 모든 점을 돌면서 상하좌우로 일직선으로 퍼져나가면서 인접한
땅을 찾는다. 만약 범위 밖으로 나가게 되었다면 그 방향은 탐색 끝이므로 break(54행), 바다라면 한 칸 더 멀리 가야하니까 continue(56행), 만약 땅을
찾았는데 같은 섬에 속한 땅이라면 마찬가지로 탐색 끝이므로 break(57행). 다른 섬에 속한 땅을 찾은 상황에서, 원래 칸에서 그 칸까지의 거리가 
2 이하라면 그 사이에 놓일 다리의 길이는 1 이하니까, edge에 넣지 않음. 거리가 2 초과라면 {다리의 길이, {원래 칸의 섬 index, 방금 찾은 칸의 섬
index}} 형태로 edge에 넣어줌(59행). 이후 크루스칼을 쓰기 위해 edge를 sort 해준다. 

과정 3)에서는 그냥 edge를 갖고 크루스칼을 쳐주면 된다. 어떠한 간선 정보를 봤는데, 그 간선이 잇는 두 섬이 서로 union 되어있는 섬들이라면 걍
패스하고, 그렇지 않다면 union 해주고 간선의 길이를 ans에 더해준다. 그 간선에 다리를 놓는 것임. 그렇게 다리를 총 island-1개 놓았다면, island개의
섬들을 모두 연결했으므로 break. 다 끝나고 82행에서, 그렇게 break한 거라면 모두 연결 성공한 것이므로 ans를 출력, 그렇지 않다면 연결 실패한 것이므로
-1을 출력한다.

처음에는 좀 복잡하고 구현할 게 많아서 어려웠던 문제. 풀고 나니깐 그냥 dfs(bfs)랑 mst(그 중에서도 크루스칼)를 혼합하면 되는 거였네.. 
그리고 모든 점들을 돌면서 4방향 일직선으로 놓을 수 있는 간선을 다 체크한다는 점에서 브루트포스였음. 왠지 board의 길이가 최대 10밖에 안 되더라.
*/