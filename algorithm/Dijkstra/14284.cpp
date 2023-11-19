#include <iostream>
#include <vector>
#include <queue>
#define MAX 5000
#define INF 1000000000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, s, t;
  int dist[MAX+1];
  vector<pair<int, int>> adj[MAX+1]; // {-비용, 도착점}
  priority_queue<pair<int, int>> pq; // {-비용, 도착점}

  cin >> N >> M;

  fill_n(dist, N+1, INF);

  while(M--){
    int a, b, c;
    
    cin >> a >> b >> c;

    adj[a].push_back({-c, b});
    adj[b].push_back({-c, a});
  }  

  cin >> s >> t;

  pq.push({0, s});

  while(!pq.empty()){
    int curCost = -pq.top().first;
    int curNode = pq.top().second;

    pq.pop();

    dist[curNode] = curCost;
    
    if(curNode == t) break;

    for(int i=0; i<adj[curNode].size(); i++){
      int nextCost = -adj[curNode][i].first;
      int nextNode = adj[curNode][i].second;

      if(dist[nextNode] != INF) continue;

      pq.push({-(curCost + nextCost), nextNode});
    }
  }

  cout << dist[t];

  return 0;
}