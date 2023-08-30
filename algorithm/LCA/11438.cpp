#include <iostream>
#include <vector>
#include <queue>
#define MAX_N 100000
#define MAX_P 17 // ceil(log_2(100000))

using namespace std;

vector<int> adj[MAX_N+1];
bool visited[MAX_N+1] = {false};

int parent[MAX_N+1][MAX_P+1]; // parent[i][j]: 노드 i의 2^j번째 부모. 값이 0이라면 없는 것이다.
int depth[MAX_N+1]; // depth[i]: 노드 i의 깊이. 루트의 깊이는 0이다.

void bfs(void);
int getLCA(int a, int b);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;

  cin >> N;

  for(int i=0; i<N-1; i++){
    int a, b;

    cin >> a >> b;

    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  bfs();

  for(int j=1; j<=MAX_P; j++){
    for(int i=2; i<=N; i++){
      if(parent[i][j-1] == 0) continue;
      parent[i][j] = parent[parent[i][j-1]][j-1];
    }
  }

  cin >> M;

  for(int i=0; i<M; i++){
    int a, b;

    cin >> a >> b;

    if(depth[a] <= depth[b]) cout << getLCA(a, b) << '\n';
    else cout << getLCA(b, a) << '\n';
  }
  
  return 0;
}

void bfs(void){
  queue<pair<int, int>> Q; // {노드 번호, 노드 깊이}

  Q.push({1, 0});

  visited[1] = true;
  parent[1][0] = 0;
  depth[1] = 0;

  while(!Q.empty()){
    int curNum = Q.front().first;
    int curDepth = Q.front().second;

    Q.pop();

    for(int i=0; i<adj[curNum].size(); i++){
      int nextNum = adj[curNum][i];

      if(visited[nextNum]) continue;

      Q.push({nextNum, curDepth + 1});

      visited[nextNum] = true;
      parent[nextNum][0] = curNum;
      depth[nextNum] = curDepth + 1;
    }
  }
}

int getLCA(int a, int b){
  int depthDiff = depth[b] - depth[a];

  for(int j=MAX_P; depthDiff; j--){
    if(parent[b][j] != 0 && (depthDiff & (1 << j))){
      b = parent[b][j];
      depthDiff &= (~(1 << j));
    }
  }

  if(a == b) return a;

  for(int j=MAX_P; j>=0; j--){
    if(parent[a][j] != 0 && parent[a][j] != parent[b][j]){
      a = parent[a][j];
      b = parent[b][j];
    }
  }

  return parent[a][0];
}

/*
11437이랑 비슷한, 입력의 크기가 커서 dp를 사용해 풀어야 하는 LCA 문제. 전체적으로 거의 비슷한데, 이번에는 getLCA 함수의 90행 for문 
부분(b를 끌어올려서, a와 b의 depth를 맞춰주는 부분)에서 비트 연산을 사용했다. 이 풀이가 더 직관적이고 좋은듯.
*/