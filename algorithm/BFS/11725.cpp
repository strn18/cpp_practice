#include <iostream>
#include <vector>
#include <queue>
#define MAX 100000

using namespace std;

vector<int> adj[MAX+1];
int parent[MAX+1];

void bfs(int start);

int main(){
  int N, a, b;

  scanf("%d", &N);

  for(int i=0; i<N-1; i++){
    scanf("%d %d", &a, &b);
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  bfs(1);

  for(int i=2; i<=N; i++)
    printf("%d\n", parent[i]);

  return 0;
}

void bfs(int start){
  queue<int> Q;
  bool visited[MAX+1] = {false};

  Q.push(start);

  while(!Q.empty()){
    int cur = Q.front();
    visited[cur] = true;
    Q.pop();

    for(int i=0; i<adj[cur].size(); i++){
      int next = adj[cur][i];
      if(!visited[next]){
        parent[next] = cur;
        Q.push(next);
      }
    }
  }
}

/*
bfs나 dfs로 간단하게 풀 수 있는 문제. 노드 1이 루트 노드일 때, 어떠한 노드의 부모 노드를 찾아야 한다. 나는 bfs로 풀었는데, 1번 노드를 시작으로
bfs를 쳐주면서, 39행의 cur의 인접 노드들 중에서 not visited한 노드를 찾으면, 그 노드의 부모는 cur 노드가 된다(46행). 
*/