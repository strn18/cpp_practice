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

/*
https://hyeo-noo.tistory.com/138 이 글을 참고하고, 시간이 오래 걸렸던 1238을 보완한 코드.
원래 풀이에서는, 어떠한 마을에서 다른 마을로 가는 다익스트라를 모든 마을에 대해 실행했기 때문에, 다익스트라 시간 * N 만큼의 시간이 걸렸다.
하지만 이 문제에서 구해야 하는 것은, 어떠한 마을에서 X 마을까지의 최소 시간과, X 마을에서 어떠한 마을까지의 최소 시간 뿐이다.
후자는 그냥 기본 다익스트라 그대로 사용하여 구하면 되는데, 전자는 구하려면 반대로 생각해야 한다.
원래 다익스트라는, 어떠한 정점에서 다른 정점들로 가는 최소 거리(여기서는 시간)를 구하는 것인데, 간선이 단방향일 때 방향을 반대로 해준다면,
다른 정점들에서 어떠한 정점으로 오는 최소 거리를 구할 수 있게 된다. 즉, 원래 dist[i]는 어떠한 정점에서 i까지의 최소 거리였다면,
간선 방향을 반대로 해주고 다익스트라를 수행한다면 dist[i]는 i에서 어떠한 정점까지의 최소 거리를 뜻하게 되는 것이다.

이걸 이용해서, rev_time 벡터를 만들어서, 출발 마을과 도착 마을을 반대로 하여 값을 넣어주었다. 그리고 dist 배열을 두 개 만들어서,
dist_to_X[i]는 i에서 X로 최소 시간(위에서 설명한, 방향을 반대로 했을 때), dist_from_X[i]는 X에서 i로 최소 시간을 뜻하도록 했다.
dist_to_X는 rev_time을 보고 다익스트라를 쳐서 채워주면 되고, dist_from_X는 time을 보고 채워주면 된다.
다익스트라를 각각 한 번씩 쳐줘서 두 배열을 채웠고, dist_to_X[i] + dist_from_X[i]의 최댓값을 찾아 출력하면 된다.

원래 다익스트라로 구하게 되는 값(어떠한 정점에서 다른 정점들로 가는 최소 거리)과 이 문제에서 필요한 값(다른 정점들에서 어떠한 정점으로 오는
최소 거리)이 반대라는 것을 파악해서, 원래 다익스트라 방식으로 문제를 풀면 비효율적이라는 걸 인지하는 것이 중요했던 문제.
*/