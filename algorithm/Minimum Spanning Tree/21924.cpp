#include <iostream>
#include <vector>
#include <queue>
#define MAX 100000

using namespace std;

vector<pair<int, int>> adj[MAX+1]; // {-비용, 연결된 건물}
priority_queue<pair<int, int>> pq; // {-비용, 연결된 건물}
bool isConnected[MAX+1] = {false};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, connected = 0;
  long long prevTotalCost = 0, totalCost = 0;

  cin >> N >> M;

  while(M--){
    int a, b, c;

    cin >> a >> b >> c;

    adj[a].push_back({-c, b});
    adj[b].push_back({-c, a});

    prevTotalCost += c;
  }

  isConnected[1] = true;
  connected++;

  for(int i=0; i<adj[1].size(); i++)
    pq.push(adj[1][i]);

  while(connected < N && !pq.empty()){
    int cost = -pq.top().first;
    int dest = pq.top().second;

    pq.pop();

    if(isConnected[dest]) continue;

    isConnected[dest] = true;
    connected++;
    totalCost += cost;

    for(int i=0; i<adj[dest].size(); i++)
      pq.push(adj[dest][i]);
  }

  cout << (connected == N ? prevTotalCost - totalCost : -1);

  return 0;
}

/*
프림 알고리즘 연습해보려고 그걸로 풀었음. 근데 크루스칼이 확실히 쉽다. 
*/