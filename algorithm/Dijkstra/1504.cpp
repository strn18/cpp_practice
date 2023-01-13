#include <iostream>
#include <vector>
#include <queue>
#define INF 700000000
#define MAX 800

using namespace std;

vector<pair<int, int>> edge[MAX+1]; // (-비용, 번호) 형태(pq와의 통일성을 위해)

void dijkstra(int start, int dist[]); // dist[i] = j라면, start번 노드에서 i번 노드까지 최소 비용이 j가 되도록 갱신해주는 함수.

int main(){
  int N, E, v1, v2;
  int dist_1[MAX+1], dist_v1[MAX+1], dist_v2[MAX+1];

  scanf("%d %d", &N, &E);

  for(int i=1; i<=N; i++){
    dist_1[i] = INF;
    dist_v1[i] = INF;
    dist_v2[i] = INF;
  }

  for(int i=0; i<E; i++){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    edge[a].push_back({-c, b});
    edge[b].push_back({-c, a});
  }

  scanf("%d %d", &v1, &v2);

  dist_1[1] = 0;
  dijkstra(1, dist_1);

  dist_v1[v1] = 0;
  dijkstra(v1, dist_v1);

  dist_v2[v2] = 0;
  dijkstra(v2, dist_v2);

  int shortest = INF; // 1->v1->v2->N 과 1->v2->v1->N 중에서 최단 경로 찾기
  shortest = min(shortest, dist_1[v1] + dist_v1[v2] + dist_v2[N]);
  shortest = min(shortest, dist_1[v2] + dist_v2[v1] + dist_v1[N]);

  if(shortest == INF)
    printf("-1");
  else
    printf("%d", shortest);

  return 0;
}

void dijkstra(int start, int dist[]){
  priority_queue<pair<int, int>> pq;

  pq.push({0, start});

  while(!pq.empty()){
    int cur_cost = -pq.top().first;
    int cur_num = pq.top().second;
    pq.pop();

    for(int i=0; i<edge[cur_num].size(); i++){
      int next_cost = -edge[cur_num][i].first;
      int next_num = edge[cur_num][i].second;

      if(cur_cost + next_cost < dist[next_num]){
        dist[next_num] = cur_cost + next_cost;
        pq.push({-dist[next_num], next_num});
      }
    }
  }
}

/*
조금 응용된 다익스트라 문제. 1에서 N으로 가야하는데, v1과 v2를 반드시 거쳐야한다는 점이 다르다. 이때 최단 경로는 두 가지 경우가 생기는데,
1) 1->v1->v2->N 이고, 2) 1->v2->v1->N 이다. 이걸 구하기 위해서는, 1에서 출발하여 i까지의 최단 경로 값 뿐만 아니라, v1과 v2에서 출발하여
i까지의 최단 경로 값 모두 구해주어야 한다. 이를 위해, 다익스트라 계산을 두 번 더(v1 출발, v2 출발) 실행해주었다.

dist_1은 1에서 출발하여 어떠한 노드 까지의 최단 경로를 담는 배열이고, dist_v1과 dist_v2는 각각 v1과 v2에서 출발하여 최단 경로를 담는 
배열이다. 출발점을 의미하는 start와, 갱신해줄 배열인 dist를 다익스트라 함수의 인자로 주어서 총 세 번 갱신해주었다.

그 다음에는, 위의 두 경로 값을 구하면서, shortest를 최솟값으로 갱신해주면 된다. 이때, 경로(1에서 N으로, v1과 v2를 거치는)가 없을 때는 
-1을 출력해주어야 하는데, 경로가 없다는 것은 44행과 45행 모두, dist_1 ~ dist_v2 중에 INF 값이 있다는 것이다(19행에서 INF로 초기화를 
해줬는데, 그대로라는 것은 경로가 없어서 갱신이 안 됐다는 거). 그렇게 되면 shortest가 원래 초기화값이었던 INF 아래로 갱신이 안 되고, 그대로
INF로 남는다. 그럴 경우, 경로가 없다는 것으로 판단하여 -1을 출력한다.

근데 처음에는 INF를 21억으로 잡았었는데, 그렇게 두니까 44행이나 45행에서 dist_1 ~ dist_v2를 더할 때 int 범위를 넘어버려서, 오버플로우가
발생했다. 그래서, dist_1 ~ dist_v2가 모두 INF여도 int 범위를 넘지 않도록 INF를 7억으로 잡았다. 
*/