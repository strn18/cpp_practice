#include <iostream>
#include <queue>
#include <vector>
#define INF 2100000000
#define MAX 20000

typedef struct{int num, weight;} info;

struct Compare{
  bool operator()(info a, info b){
    return a.weight > b.weight;
  }
};

using namespace std;

int main(){
  int V, E, K;
  int dist[MAX+1]; // dist[i]: K번 -> i번 노드로의 최단 경로값
  vector<info> edge[MAX+1]; // edge[i]의 원소 (num, weight): i번 노드에서 num번 노드를 향하는 가중치 weight의 간선이 있다.

  scanf("%d %d", &V, &E);
  scanf("%d", &K);

  for(int i=1; i<=V; i++)
    dist[i] = (i==K ? 0 : INF);

  for(int i=0; i<E; i++){
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    edge[u].push_back({v, w});
  }

  // dijkstra
  priority_queue<info, vector<info>, Compare> pq;
  pq.push({K, dist[K]});

  while(!pq.empty()){
    info cur = pq.top();
    pq.pop();

    for(int i=0; i<edge[cur.num].size(); i++){
      info next = edge[cur.num][i];

      if(cur.weight + next.weight < dist[next.num]){
        dist[next.num] = cur.weight + next.weight;
        pq.push({next.num, dist[next.num]});
      }
    }
  }

  for(int i=1; i<=V; i++){
    if(dist[i] == INF)
      printf("INF\n");
    else
      printf("%d\n", dist[i]);
  }

  return 0;
}

/*
기본적인 다익스트라 문제. 방향 그래프라는 점이 좀 특이했는데, 풀이가 크게 달라진 점은 없고 (u, v, w)라는 입력을 받았을 때 그냥 벡터[u]에만
간선을 추가해주면 된다. 
나는 다익스트라의 pq를 쓸 때, (노드 번호, 가중치(그 노드까지 가는 비용))의 형태로 구조체를 만들어서 쓰는데, 다른 사람들은 주로 pair형을 쓰고,
가중치에 -를 곱해서 쓰더라. Compare 구조체를 따로 선언하기 귀찮아서 그런듯.
*/