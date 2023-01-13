/*
#include <iostream>
#include <queue>
#include <string.h>

using namespace std;

int edge[1001][1001] = {0};
int visited[1001] = {0};
queue<int> Q;

int N, M; // 정점 수, 간선 수

void DFS(int v);
void BFS(int v);

int main(){
  int V, v1, v2;
  
  scanf("%d %d %d", &N, &M, &V);

  for(int i=0; i<M; i++){
    scanf("%d %d", &v1, &v2);
    edge[v1][v2] = 1;
    edge[v2][v1] = 1;
  }

  DFS(V);
  printf("\n");
  memset(visited+1, 0, N*sizeof(int));
  
  BFS(V);

  return 0;  
}

void DFS(int v){
  visited[v] = 1;
  printf("%d ", v);

  for(int i=1; i<=N; i++)
    if(edge[v][i] && !visited[i])
      DFS(i);
}

void BFS(int v){
  int cur_v;
  visited[v] = 1;
  printf("%d ", v);
  Q.push(v);
  
  while(!Q.empty()){
    cur_v = Q.front();
    Q.pop();

    for(int i=1; i<=N; i++){
      if(edge[cur_v][i] && !visited[i]){
        visited[i] = 1;
        printf("%d ", i);
        Q.push(i);
      }
    }
  }
}

그냥 DFS랑 BFS 탐색 순서대로 번호 출력하는 문제인데, 특이점으로는 인접리스트가 아니라 인접행렬을 썼을 때 풀기 쉽게 의도된 것 같다는 점. 두 정점 사이에 여러 개의 간선이 있을 수 있다는 것이 문제 조건이었는데, (1, 4)가 이미 입력됐는데 (4, 1)이 또 입력될 수 있다는 것임. 근데 이때 인접리스트를 쓰면(벡터 사용) 인덱스 1인 벡터에 4라는 값이 두 개 추가되는 문제가 발생함. 물론 벡터 안을 살펴보고 같은 게 있으면 푸시하지 않는 방법도 있겠지만, 정점의 수가 적게 제시되었기 때문에 인접행렬을 써도 된다고 판단하였음. 인접행렬을 쓸 경우 edge[1][4] = 1 이런 식으로 두 점 사이에 간선이 있으면 1을 넣는 방식이기 때문에 여러번 수행되어도 문제 발생 x 그래서 사용함. 이거 말고는 자잘한 실수 제외하면 딱히 특이점은 없었다.
*/