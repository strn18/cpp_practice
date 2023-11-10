#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#define MAX 500

using namespace std;

int n, m;
vector<int> adj[MAX+1];
bool visited[MAX+1];

void initialize(void);
bool hasCycle(int prev, int cur);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  for(int t=1; 1; t++){
    int treeCount = 0;
    string ans;

    cin >> n >> m;

    if(n == 0) break;

    initialize();

    while(m--){
      int a, b;

      cin >> a >> b;

      adj[a].push_back(b);
      adj[b].push_back(a);
    }

    for(int i=1; i<=n; i++){
      if(!visited[i] && !hasCycle(0, i))
        treeCount++;
    }

    cout << "Case " << t << ": ";

    if(treeCount == 0) cout << "No trees.\n";
    else if(treeCount == 1) cout << "There is one tree.\n";
    else cout << "A forest of " << treeCount << " trees.\n";
  }

  return 0;
}

void initialize(void){
  for(int i=1; i<=n; i++)
    adj[i].clear();

  memset(visited, false, sizeof(bool)*(n+1));
}

bool hasCycle(int prev, int cur){
  if(visited[cur]) return true;

  visited[cur] = true;

  for(int i=0; i<adj[cur].size(); i++){
    int next = adj[cur][i];

    if(next == prev) continue;
    if(hasCycle(cur, next)) return true;
  }

  return false;
}

/*
분리 집합 풀려고 찾아서 풀었는데 문제 읽다보니까 그냥 dfs로 풀 수 있었던 문제. 1~n번 노드를 돌면서 not visited일 경우 dfs를 치는데, 만약 치면서 
방문한 노드를 다시 방문하게 된다면(62행), 거기엔 사이클이 있는 것이므로 트리가 아니기에 treeCount를 늘리지 않는다(40행). 참고로, dfs로 이렇게 
사이클 탐색을 하려면 바로 이전 노드(prev)로는 dfs를 뻗어나가면 안 된다. 이전 노드는 방문 표시가 되어 있기에, 그렇게 하면 사이클로 판정해버림. 
*/