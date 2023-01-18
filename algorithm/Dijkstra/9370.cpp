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

/*
좀 꼬아놔서 까다로웠던 다익스트라 문제. s에서 x까지 갈 때, 그 경로에 g->h 또는 h->g가 있는지 판별하는 문제다.
처음에는 간단하게 prev 배열을 만들고, prev[i] = j라면, s에서 i로 갈 때 i 직전에 j에 도착했음을 의미하도록 했다. 그런 다음에, 
x에서 시작해서, x = prev[x]를 해주며 점점 s로 내려가면서, (x, prev[x])가 (g, h) 또는 (h, g)라면 x를 출력해주면 된다. 만약 x가 s가
될 때까지 조건을 만족하지 못했으면 출력하지 않는다.
간단해보이는 문제였는데, 이렇게 제출하니 틀렸다. 사실 생각해보면, s에서 x로 갈 때 최단 경로가 여러 개일 수 있는데, 내가 짠 방식은
최단 경로를 딱 하나만 기억한다. 그래서 기억한 최단 경로에 g->h나 h->g가 없으면 x를 출력하지 않는데, 총 거리가 같은 다른 최단 경로에는
그게 있을 경우, x를 출력하는 것이 정답이므로 틀리게 된다.
그래서 prev를 벡터형 배열로 만들고 여러 경로를 기억하게 해야하나? 해서 이리저리 짜봤는데 코드가 너무 복잡해짐.

고민 좀 하다가 https://yabmoons.tistory.com/390 여기를 살짝 참고했다. 해결 방식은, g에서 시작하는 dist와 h에서 시작하는 dist를 따로
만들어놓고, dist(s->g) + dist(g->h) + dist(h->x) 또는 dist(s->h) + dist(h->g) + dist(g->x)가 dist(s->x)와 같다면, s에서 x로 갈 때
g와 h 사이의 길을 거쳤다는 것이다. 위에서 말했던 것처럼 s에서 x로 갈 때 최단 경로가 여러 개일 수 있는데, 그걸 하나하나 고려하는 건 힘들다.
그렇기 때문에 s->x로 가는 최단 경로를 하나하나 찾아보는 것이 아니라, s->g->h->x 또는 s->h->g->x의 경로가 최단 경로와 거리가 같다면, 걔들도
최단 경로인 것이니까(최단 경로랑 거리가 같으니 최단 경로임), g와 h 사이의 길을 거쳤다고 볼 수 있는 것임. 
*/