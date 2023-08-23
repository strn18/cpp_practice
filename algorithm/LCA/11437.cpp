#include <iostream>
#include <vector>
#include <queue>
#define MAX_N 50000
#define MAX_P 16 // ceil(log_2(50000))

using namespace std;

vector<int> adj[MAX_N + 1];
int parent[MAX_N + 1][MAX_P + 1];
int depth[MAX_N + 1];

void bfs(void);
int findLCA(int a, int b); // 노드 a와 노드 b의 LCA를 리턴한다. 이때, 노드 b의 깊이가 반드시 깊도록 한다.

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;

  cin >> N;

  for(int i=2; i<=N; i++) // 우선 parent를 -1로 모두 초기화.
    for(int j=0; j<=MAX_P; j++)
      parent[i][j] = -1;

  for(int i=0; i<N-1; i++){
    int a, b;

    cin >> a >> b;

    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  bfs(); // bfs를 돌려 i = [2, N]에 대해 parent[i][0]과 depth[i]를 채운다.

  for(int j=1; j<=MAX_P; j++) // bottom-up으로 parent를 마저 채운다.
    for(int i=2; i<=N; i++)
      if(parent[i][j-1] != -1)
        parent[i][j] = parent[parent[i][j-1]][j-1];

  cin >> M;

  while(M--){
    int a, b;

    cin >> a >> b;
    
    if(depth[a] <= depth[b]) cout << findLCA(a, b) << '\n';
    else cout << findLCA(b, a) << '\n';
  }

  return 0;
}

void bfs(void){
  bool visited[MAX_N + 1] = {false};
  queue<pair<int, int>> Q; // {노드 번호, 노드 깊이}

  Q.push({1, 0});
  visited[1] = true;
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
      depth[nextNum] = curDepth + 1;
      parent[nextNum][0] = curNum;
    }
  }
}

int findLCA(int a, int b){
  int diff = depth[b] - depth[a];

  for(int j=0; diff != 0; j++){ // a와 b의 높이가 같아질 때까지 b를 높인다. 
  // 가령, 높이 차이가 11 = 1 + 2 + 8 이라면? b를 위로 1칸, 2칸, 0칸, 8칸 높이게 되어 a와 b의 높이가 같아지는 것.
    if(diff % 2) b = parent[b][j];
    diff /= 2;
  }
  
  if(a == b) return a;

  for(int j=MAX_P; j>=0; j--){
    if(parent[a][j] != -1 && parent[a][j] != parent[b][j]){
      a = parent[a][j];
      b = parent[b][j];
    }
  }

  return parent[a][0];
}

/*
SWEA 기초학습 No_17 풀고 LCA 공부한 다음 백준에서 풀어본 문제. 
전체적으로는 큰 차이 없고, 걍 공부할 때 본 https://blog.naver.com/kks227/220820773477 여기랑 SWEA No_17 설명 참고하면 된다.
*/