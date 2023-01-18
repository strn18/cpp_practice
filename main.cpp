#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define INF 99999999
#define MAX 2000

using namespace std;

void dijkstra(int start, int dist[], vector<pair<int, int>> road[]);

int main(){
  int T;

  scanf("%d", &T);

  while(T--){
    int n, m, t;
    int s, g, h;
    int dist_from_s[MAX+1], dist_from_g[MAX+1], dist_from_h[MAX+1];
    vector<pair<int, int>> road[MAX+1];

    // input
    scanf("%d %d %d", &n, &m, &t);
    scanf("%d %d %d", &s, &g, &h);

    for(int i=0; i<m; i++){
      int a, b, d;

      scanf("%d %d %d", &a, &b, &d);
      road[a].push_back({-d, b});
      road[b].push_back({-d, a});
    }

    // initialize dist
    for(int i=1; i<=n; i++){
      dist_from_s[i] = INF;
      dist_from_g[i] = INF;
      dist_from_h[i] = INF;
    }

    //dijkstra
    dijkstra(s, dist_from_s, road);
    dijkstra(g, dist_from_g, road);
    dijkstra(h, dist_from_h, road);
    
    // get x
    int x[100];
    for(int i=0; i<t; i++)
      scanf("%d", &x[i]);
    sort(x, x+t);
    
    // output
    for(int i=0; i<t; i++){
      if(dist_from_s[x[i]] == dist_from_s[g] + dist_from_g[h] + dist_from_h[x[i]])
        printf("%d ", x[i]);
      else if(dist_from_s[x[i]] == dist_from_s[h] + dist_from_h[g] + dist_from_g[x[i]])
        printf("%d ", x[i]);
      else
        continue;
    }
  }

  return 0;
}

void dijkstra(int start, int dist[], vector<pair<int, int>> road[]){
  dist[start] = 0;
  priority_queue<pair<int, int>> pq;
  pq.push({-dist[start], start});

  while(!pq.empty()){
    int cur_dist = -pq.top().first;
    int cur_num = pq.top().second;
    pq.pop();

    if(dist[cur_num] < cur_dist) continue;

    for(int i=0; i<road[cur_num].size(); i++){
      int next_dist = -road[cur_num][i].first;
      int next_num = road[cur_num][i].second;

      if(cur_dist + next_dist < dist[next_num]){
        dist[next_num] = cur_dist + next_dist;
        pq.push({-dist[next_num], next_num});
      }
    }
  }
}