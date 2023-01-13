/*
#include <iostream>
#include <vector>
#include <string.h>
#define MAX 20000

using namespace std;

vector<int> adj[MAX+1];
int color[MAX+1];
int flag;

void dfs(int prev, int cur);

int main(){
  int K;
  scanf("%d", &K);

  for(int i=0; i<K; i++){
    int V, E, u, v;
    scanf("%d %d", &V, &E);

    memset(color, 0, (V+1)*sizeof(int));
    flag = 0;
    
    for(int j=0; j<E; j++){
      scanf("%d %d", &u, &v);
      adj[u].push_back(v);
      adj[v].push_back(u);
      }

    for(int j=1; j<=V; j++)
      if(!color[j])
        dfs(2, j);
    
    if(flag)
      printf("NO\n");
    else
      printf("YES\n");

    for(int j=1; j<=V; j++)
      adj[j].clear();
  }
  
  return 0;
}

void dfs(int prev, int cur){
  color[cur] = (prev==1) ? 2 : 1;
  
  for(int i=0; i<adj[cur].size(); i++){
    int next = adj[cur][i];
    if(!color[next])
      dfs(color[cur], next);
    else if(color[next] == color[cur]){
      flag = 1;
      return;
    }
  }
}

좃같았던 문제;; 처음에는 이분 그래프가 사이클이 없는 그래프를 뜻하는 줄 알고(각 집합에 속하는 정접끼리 인접하면 안 되는 것 뿐만 아니라 아예 연결이 되면 안 되는 걸로 알았음) 똥꼬쇼해서 코드 뱉어내서 거의 다 한 상태에서 문제를 다시 읽어보니 인접만 안 하면 됐던 것..
그래서 dfs로 그래프를 돌면서, 인접 노드의 색이 아직 0이면 현재 노드의 색과 다른 색으로 칠하고, 인접 노드의 색이 있을 때 현재 노드의 색과 같다면 flag를 1로 하고 리턴해서 이분 그래프가 아님을 얻어내는 식으로 짰다. 사실 이걸 떠올리는 건 별로 오래 안 걸렸는데, 제출하니까 틀렸음. 아무리 고민해도 틀린 부분이 없는데 싶어서 검색해보니까, 그래프가 모두 연결되어 있다는 보장이 없으니(동떨어져있는 노드가 있을 수 있으니) dfs를 노드 1에만 쓰는 게 아니라 32행처럼 반복해서 실행해야 했던 것임. 그래서 그 부분 고치니까 맞았다.
아니 하나도 안 어려운 문젠데 1) 문제 제대로 이해 못해서 2) 그래프 연결 어쩌고 부분
때문에 시간만 뒤지게 잡아먹었네
*/