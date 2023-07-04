#include <iostream>
#include <queue>
#include <vector>
#define MAX 10000
#define INF 2100000000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, D;
  int dist[MAX+1];
  vector<pair<int, int>> road[MAX+1];
  priority_queue<pair<int, int>> pq;

  cin >> N >> D;

  for(int i=0; i<N; i++){
    int a, b, c;
    cin >> a >> b >> c;
    if(b <= D) road[a].push_back({-c, b});
  }

  for(int i=0; i<=D; i++){
    road[i].push_back({-1, i+1});
    dist[i] = INF;
  }
  
  pq.push({0, 0});

  while(!pq.empty()){
    int cur_cost = -pq.top().first;
    int cur_num = pq.top().second;
    
    pq.pop();

    if(dist[cur_num] != INF) continue;
    dist[cur_num] = cur_cost;

    if(cur_num == D) break;

    for(int i=0; i<road[cur_num].size(); i++){
      int next_cost = -road[cur_num][i].first;
      int next_num = road[cur_num][i].second;

      if(dist[next_num] != INF) continue;
      pq.push({-(cur_cost + next_cost), next_num});
    }
  }

  cout << dist[D];

  return 0;
}

/*
약간 변형된 다익스트라 문제. 다익스트라 안 써도 풀 수 있다. https://astrid-dm.tistory.com/439 이렇게.
모든 위치(0m, 1m, 2m, ... Dm 지점)를 하나의 정점으로 보고, 주어진 지름길을 간선으로 본다. 또한, im 지점은 i+1m 지점으로의 간선이 있다고 볼 수
있다. 이를 이용하여 다익스트라를 쳐준다. 
*/