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

/*
오랜만에 풀어본 다익스트라 문제. 좀 헷갈렸지만 그래도 잘 풀었다.

의존성 입력으로 (a, b, s)가 주어지면, a는 b가 감염되고 s초 후에 감염된다는 뜻이다. 즉, b에서 a로 가는 데 s초가 걸린다고 생각하면 된다.
이걸 이용해서, 입력을 잘 받는다. dist[i] = c가 감염된 후 i가 감염되는 데 걸리는 시간. 이고, time[i] = {b, c} 형태라면, i가 감염된 후 
c가 감염되는 데 -b초가 걸린다는 뜻이다. 시간을 기준으로 최솟값 pq를 사용하기 위해 -부호를 붙여 사용했다.
나머지 부분도 그냥 전형적인 다익스트라 문제임. dist를 잘 구한 다음, 값이 INF(해당 노드는 감염되지 않는다는 소리)인 노드를 제외하고 개수를
세서 total_com을 구하고, 가장 오래 걸리는 감염 시간을 구해서 totla_time을 구하면 됨.
*/