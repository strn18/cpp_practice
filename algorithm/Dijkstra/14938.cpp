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

/*
쉬웠던 다익스트라 문제. 어떠한 지역(정점)에서, 다른 지역으로 가는 최소 거리를 다익스트라로 모두 구한 후, 최소 거리가 m 이하인 지역들을 찾아서,
해당 지역들의 items 값을 다 더하면 그 어떠한 지역에 떨어졌을 때 먹을 수 있는 아이템 개수를 구할 수 있다. 다만, 이때 어느 지역에 떨어져야 먹을
수 있는 아이템 개수가 최대인지를 구하기 위해서, 모든 지역에 대해서 다익스트라를 쳐줘야한다. 

이를 위해, start번 지역을 시작으로 다익스트라를 치는 함수인 dijkstra를 만들었고, 최소 거리를 모두 구한 뒤에는 start번 지역에 떨어졌을 때 
먹을 수 있는 아이템 개수를 구해서 ans를 최댓값으로 갱신시켜줬다(65~69행).

지역과 간선의 개수가 적어서 다익스트라로도 쉽게 풀었는데, 플로이드 와샬을 쓰면 더 좋을 것 같다. 다익스트라는 어떠한 정해진 정점에서 다른 
정점으로의 최소 거리를 구하는데, 플로이드 와샬은 모든 정점에서 모든 정점으로의 최소 거리를 구한다고 함. 다음에 공부해봐야지
*/