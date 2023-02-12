#include <iostream>
#include <vector>
#include <queue>
#define INF 2100000000
#define MAX 100

using namespace std;

int n, m, ans = 0;
int items[MAX+1];
vector<pair<int, int>> road[MAX+1];

void dijkstra(int start);

int main(){
  int r;

  scanf("%d %d %d", &n, &m, &r);
  for(int i=1; i<=n; i++)
    scanf("%d", &items[i]);
  for(int i=0; i<r; i++){
    int a, b, l;
    scanf("%d %d %d", &a, &b, &l);
    road[a].push_back({-l, b});
    road[b].push_back({-l, a});
  }

  for(int i=1; i<=n; i++)
    dijkstra(i);
  
  printf("%d", ans);

  return 0;
}

void dijkstra(int start){
  int count = 0;
  int dist[MAX+1];
  
  for(int i=1; i<=n; i++)
    dist[i] = INF;
  dist[start] = 0;

  priority_queue<pair<int, int>> pq;
  pq.push({0, start});

  while(!pq.empty()){
    int cur_cost = -pq.top().first;
    int cur_pos = pq.top().second;
    pq.pop();

    if(cur_cost > dist[cur_pos]) continue;

    for(int i=0; i<road[cur_pos].size(); i++){
      int next_cost = -road[cur_pos][i].first;
      int next_pos = road[cur_pos][i].second;

      if(cur_cost + next_cost < dist[next_pos]){
        dist[next_pos] = cur_cost + next_cost;
        pq.push({-dist[next_pos], next_pos});
      }
    }
  }

  for(int i=1; i<=n; i++)
    if(dist[i] <= m)
      count += items[i];
  
  ans = max(ans, count);
}