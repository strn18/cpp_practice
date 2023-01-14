#include <iostream>
#include <queue>
#include <vector>
#define INF 2100000000
#define MAX 300000

using namespace std;

int dist[MAX+1];
bool visited[MAX+1];
vector<int> road[MAX+1];

int main(){
  int N, M, K, X;
  bool flag = false;

  scanf("%d %d %d %d", &N, &M, &K, &X);

  for(int i=0; i<M; i++){
    int A, B;
    scanf("%d %d", &A, &B);
    road[A].push_back(B);
  }

  for(int i=1; i<=N; i++){
    dist[i] = INF;
    visited[i] = false;
  }
  dist[X] = 0;

  queue<pair<int, int>> pq;
  pq.push({-dist[X], X});

  while(!pq.empty()){
    int cur_cost = -pq.front().first;
    int cur_num = pq.front().second;
    pq.pop();

    if(visited[cur_num] || cur_cost>=K) continue;
    visited[cur_num] = true;

    for(int i=0; i<road[cur_num].size(); i++){
      int next_num = road[cur_num][i];

      if(cur_cost+1 < dist[next_num]){
        dist[next_num] = cur_cost+1;
        pq.push({-dist[next_num], next_num});
      }
    }
  }

  for(int i=1; i<=N; i++){
    if(dist[i] == K){
      printf("%d\n", i);
      flag = true;
    }
  }

  if(!flag)
    printf("-1");

  return 0;
}

/*
난이도가 낮았던 다익스트라 문제. 사실 bfs 문제이기도 함.
노드 사이 간선이 단방향이고, 간선의 가중치는 반드시 1이다. 그렇기에 사실 가중치 없다고 생각하고, 노드와 노드 사이가 이어져있다고 생각하면,
bfs로 풀 수도 있을 것임. 일단 나는 다익스트라로 풀었다.

전형적인 다익스트라 풀이 방식으로 푸니까 맞았음(첫번째 제출). 근데 풀고 나서, while문의 cur_cost가 이미 K라면, 거기서 더 이상 탐색할 필요가
없을 것이라 생각하고, 39행의 if문을 추가했다. 그리고 1916 풀면서, pq로 푸는 다익스트라 방식에 visited를 썼던 게 생각나서(visited 안 썼을 땐
시간초과 났었음) 그것도 추가했다. 근데 제출하니까 맞긴 했는데 시간은 별로 안 줄었음..

그리고 다른 사람들 풀이 보면서, 어차피 간선 가중치가 반드시 1이라 pq를 쓸 필요가 없다는 걸 알게 되었다(큐에 넣으면 어차피 그대로 cost 기준
오름차순이라, 최솟값을 찾을 필요가 없다). 그래서 큐로 바꿨더니 시간이 쪼금 줄었음.
*/