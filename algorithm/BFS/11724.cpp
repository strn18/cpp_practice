#include <iostream>
#include <vector>
#include <queue>
#define MAX 1000

using namespace std;

int count = 0;
vector<int> adj[MAX+1];

void bfs(int N);

int main(){
  int N, M, u, v;

  scanf("%d %d", &N, &M);
  for(int i=0; i<M; i++){
    scanf("%d %d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  bfs(N);

  printf("%d", count);

  return 0;
}

void bfs(int N){
  queue<int> Q;
  bool visited[MAX+1] = {false};

  for(int i=1; i<=N; i++){
    if(!visited[i]){
      count++;
      Q.push(i);
      visited[i] = true;

      while(!Q.empty()){
        int cur = Q.front();
        Q.pop();
        
        for(int i=0; i<adj[cur].size(); i++){
          int next = adj[cur][i];
          if(!visited[next]){
            Q.push(next);
            visited[next] = true;
          }
        }
      }
    }
  }
}

/*
쉬운 bfs 문제. bfs든 dfs든 어쨌든 연결된 노드를 모두 탐색하는 방식이면 됨.
*/