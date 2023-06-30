#include <iostream>
#include <vector>
#include <queue>
#define MAX 1000
#define INF 2100000000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;

  int dist[MAX+1];
  vector<pair<int, int>> adj[MAX+1]; // {-거리, 도착 지점}
  priority_queue<pair<int, pair<int, int>>> pq; // {-거리, {중간 지점, 도착 지점}}

  int ans[MAX+1];

  cin >> N >> M;

  for(int i=1; i<=N; i++)
    dist[i] = INF;

  for(int i=0; i<M; i++){
    int A, B, C;

    cin >> A >> B >> C;

    adj[A].push_back({-C, B});
    adj[B].push_back({-C, A});
  }

  pq.push({0, {1, 1}});

  while(!pq.empty()){
    int cur_cost = -pq.top().first;
    int prev_num = pq.top().second.first;
    int cur_num = pq.top().second.second;

    pq.pop();

    if(dist[cur_num] != INF) continue;

    dist[cur_num] = cur_cost;
    ans[cur_num] = prev_num;

    for(int i=0; i<adj[cur_num].size(); i++){
      int next_cost = -adj[cur_num][i].first;
      int next_num = adj[cur_num][i].second;

      if(dist[next_num] != INF) continue;

      pq.push({-(cur_cost + next_cost), {cur_num, next_num}});
    }
  }

  cout << N-1 << '\n';

  for(int i=2; i<=N; i++)
    cout << ans[i] << ' ' << i << '\n';

  return 0;
}