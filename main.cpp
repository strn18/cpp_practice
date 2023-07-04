#include <iostream>
#include <vector>
#define MAX 100000

using namespace std;

bool visited[MAX+1] = {false};
int dist[MAX+1];
vector<pair<int, int>> adj[MAX+1];

void dfs(int start, int count);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int V, max_dist = 0, max_num = 0, ans = 0;

  cin >> V;

  for(int i=0; i<V; i++){
    int a, b, c;

    cin >> a;

    while(true){
      cin >> b;
      if(b == -1) break;
      cin >> c;
      adj[a].push_back({b, c});
    }
  }

  dfs(1, 0);

  for(int i=1; i<=V; i++){
    if(dist[i] > max_dist){
      max_dist = dist[i];
      max_num = i;
    }

    visited[i] = false;
  }

  dfs(max_num, 0);

  for(int i=1; i<=V; i++)
    ans = max(ans, dist[i]);

  cout << ans;

  return 0;
}

void dfs(int start, int count){
  visited[start] = true;
  dist[start] = count;

  for(int i=0; i<adj[start].size(); i++){
    int next = adj[start][i].first;
    
    if(!visited[next]) dfs(next, count+adj[start][i].second);
  }
}