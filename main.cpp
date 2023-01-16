#include <iostream>
#include <vector>
#include <queue>
#define INF 2100000000
#define MAX 1000

using namespace std;

int main(){
  int n, m, start, end;
  int dist[MAX+1]; // dist[i]: start에서 i로 가는 최소 비용
  int prev[MAX+1]; // prev[i]: start에서 i로 최소로 갈 때, i 이전 도시
  vector<pair<int, int>> bus[MAX+1]; // (-비용, 도착 도시)

  scanf("%d", &n);
  scanf("%d", &m);
  for(int i=0; i<m; i++){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    bus[a].push_back({-c, b});
  }
  scanf("%d %d", &start, &end);

  for(int i=1; i<=MAX; i++)
    dist[i] = INF;
  dist[start] = 0;

  priority_queue<pair<int, int>> pq; // (-비용, 도착 도시)
  pq.push({0, start});

  while(!pq.empty()){
    int cur_cost = -pq.top().first;
    int cur_num = pq.top().second;
    pq.pop();
    
    if(dist[cur_num] < cur_cost) continue;

    for(int i=0; i<bus[cur_num].size(); i++){
      int next_cost = -bus[cur_num][i].first;
      int next_num = bus[cur_num][i].second;

      if(cur_cost + next_cost < dist[next_num]){
        dist[next_num] = cur_cost + next_cost;
        prev[next_num] = cur_num;
        pq.push({-dist[next_num], next_num});
      }
    }
  }

  printf("%d\n", dist[end]);

  vector<int> cities;
  cities.push_back(end);
  int prev_city = end;

  while(prev_city != start){
    prev_city = prev[prev_city];
    cities.push_back(prev_city);
  }

  printf("%d\n", cities.size());
  
  for(int i=cities.size()-1; i>=0; i--)
    printf("%d ", cities[i]);

  return 0;
}