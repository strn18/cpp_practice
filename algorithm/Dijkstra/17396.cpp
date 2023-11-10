#include <iostream>
#include <queue>
#include <vector>
#define ll long long
#define MAX 100000

using namespace std;

bool visited[MAX] = {false};
vector<pair<ll, int>> adj[MAX]; // {-비용, 간선}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;
  ll ans = -1;
  bool seen[MAX];
  priority_queue<pair<ll, int>> pq;

  cin >> N >> M;

  for(int i=0; i<N; i++)
    cin >> seen[i];
  
  for(int i=0; i<M; i++){
    int a, b, t;

    cin >> a >> b >> t;

    if((seen[a] && a != N-1) || (seen[b] && b != N-1)) continue;

    adj[a].push_back({-t, b});
    adj[b].push_back({-t, a});
  }

  // dijkstra
  pq.push({0, 0});

  while(!pq.empty()){
    ll curCost = -pq.top().first;
    int curNode = pq.top().second;

    pq.pop();

    if(visited[curNode]) continue;

    if(curNode == N-1){
      ans = curCost;
      break;
    }

    visited[curNode] = true;

    for(int i=0; i<adj[curNode].size(); i++){
      ll nextCost = -adj[curNode][i].first;
      int nextNode = adj[curNode][i].second;

      if(visited[nextNode]) continue;

      pq.push({-(curCost + nextCost), nextNode});
    }
  }

  cout << ans;

  return 0;
}

/*
그냥 다익스트라 문제인데, cost가 int를 넘어갈 수 있어서 long long으로 해야 함. 
*/