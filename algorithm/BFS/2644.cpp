#include <iostream>
#include <vector>
#include <queue>
#define MAX 100

using namespace std;

vector<int> adj[MAX+1];
int dist[MAX+1];

void bfs(int start);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, a, b, m;

  cin >> n >> a >> b >> m;

  for(int i=1; i<=n; i++)
    dist[i] = -1;

  for(int i=0; i<m; i++){
    int x, y;

    cin >> x >> y;

    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  bfs(a);

  cout << dist[b];

  return 0;
}

void bfs(int start){
  queue<int> Q;

  dist[start] = 0;
  Q.push(start);

  while(!Q.empty()){
    int cur = Q.front();
    Q.pop();

    for(int i=0; i<adj[cur].size(); i++){
      int next = adj[cur][i];

      if(dist[next] != -1) continue;

      dist[next] = dist[cur]+1;
      Q.push(next);
    }
  }
}

/*
기초 bfs 문제.
*/