#include <iostream>
#include <vector>
#include <queue>
#define INF 99999999
#define MAX 1000

using namespace std;

void dijkstra(int start, int dist[], vector<pair<int, int>> time[]); // time을 보고, start에서 시작하여 dist 채우기

int main(){
  int N, M, X;
  int longest = -1;
  int dist_to_X[MAX+1], dist_from_X[MAX+1]; // dist_to_X[i]: i에서 X로 최소 시간. dist_from_X[i]: X에서 i로 최소 시간.
  vector<pair<int, int>> time[MAX+1], rev_time[MAX+1];

  scanf("%d %d %d", &N, &M, &X);

  for(int i=0; i<M; i++){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    time[a].push_back({-c, b});
    rev_time[b].push_back({-c, a});
  }

  for(int i=1; i<=N; i++){
    dist_to_X[i] = INF;
    dist_from_X[i] = INF;
  }

  dijkstra(X, dist_to_X, rev_time); // 거꾸로 뒤집은 rev_time을 이용하여, 다른 도시에서 X로의 최소 시간을 구한다.
  dijkstra(X, dist_from_X, time); // time을 이용하여, X에서 다른 도시로의 최소 시간을 구한다.

  for(int i=1; i<=N; i++)
    longest = max(longest, dist_to_X[i] + dist_from_X[i]);

  printf("%d", longest);

  return 0;
}

void dijkstra(int start, int dist[], vector<pair<int, int>> time[]){
  dist[start] = 0;
  priority_queue<pair<int, int>> pq;
  pq.push({-dist[start], start});

  while(!pq.empty()){
    int cur_time = -pq.top().first;
    int cur_num = pq.top().second;
    pq.pop();

    if(cur_time > dist[cur_num]) continue;

    for(int i=0; i<time[cur_num].size(); i++){
      int next_time = -time[cur_num][i].first;
      int next_num = time[cur_num][i].second;

      if(cur_time + next_time < dist[next_num]){
        dist[next_num] = cur_time + next_time;
        pq.push({-dist[next_num], next_num});
      }
    }
  }
}