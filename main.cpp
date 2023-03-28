#include <iostream>
#include <vector>
#include <queue>
#define MAX 10000
#define INF 2100000000

using namespace std;

int main(){
  int T;

  scanf("%d", &T);

  while(T--){
    int n, d, c, a, b, s;
    int total_com = 0, total_time = 0;
    int dist[MAX+1];
    vector<pair<int, int>> time[MAX+1];

    scanf("%d %d %d", &n, &d, &c);

    for(int i=1; i<=n; i++)
      dist[i] = (i==c ? 0 : INF);

    while(d--){
      scanf("%d %d %d", &a, &b, &s);
      time[b].push_back({-s, a});
    }

    // dijkstra
    priority_queue<pair<int, int>> pq;
    pq.push({-dist[c], c});

    while(!pq.empty()){
      int cur_num = pq.top().second;
      int cur_cost = -pq.top().first;
      pq.pop();

      for(int i=0; i<time[cur_num].size(); i++){
        int next_num = time[cur_num][i].second;
        int next_cost = -time[cur_num][i].first;

        if(cur_cost + next_cost < dist[next_num]){
          dist[next_num] = cur_cost + next_cost;
          pq.push({-dist[next_num], next_num});
        }
      }
    }

    for(int i=1; i<=n; i++){
      if(dist[i] != INF){
        total_com++;
        total_time = max(total_time, dist[i]);
      }
    }

    printf("%d %d\n", total_com, total_time);
  }
  
  return 0;
}