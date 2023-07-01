#include <iostream>
#include <vector>
#include <queue>
#define MAX 50000
#define INF 2100000000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;

  int cost[MAX+1];
  vector<pair<int, int>> road[MAX+1];
  priority_queue<pair<int, int>> pq;
  
  cin >> N >> M;

  for(int i=1; i<=N; i++)
    cost[i] = INF;

  for(int i=0; i<M; i++){
    int A, B, C;

    cin >> A >> B >> C;

    road[A].push_back({-C, B});
    road[B].push_back({-C, A});
  }

  pq.push({0, 1});

  while(!pq.empty()){
    int cur_cost = -pq.top().first;
    int cur_num = pq.top().second;

    pq.pop();

    if(cost[cur_num] != INF) continue;
    cost[cur_num] = cur_cost;

    for(int i=0; i<road[cur_num].size(); i++){
      int next_cost = -road[cur_num][i].first;
      int next_num = road[cur_num][i].second;

      if(cost[next_num] != INF) continue;

      pq.push({-(cur_cost + next_cost), next_num});
    }
  }

  cout << cost[N];

  return 0;
}

/*
그냥 평범한 다익스트라 문제. 
*/