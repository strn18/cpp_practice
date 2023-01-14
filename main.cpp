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