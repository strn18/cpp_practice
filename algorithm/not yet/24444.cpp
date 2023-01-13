/*
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

queue<int> Q;
int visited[100001] = {0};
vector<int> E[100001];

int cur_rank = 1;
int ranking[100001] = {0};

void bfs(int R);

int main(){
  int N, M, R, u, v;
  scanf("%d %d %d", &N, &M, &R);
  for(int i=0; i<M; i++){
    scanf("%d %d", &u, &v);
    E[u].push_back(v);
    if(u!=v)
      E[v].push_back(u);
  }

  bfs(R);

  for(int i=1; i<=N; i++)
    printf("%d\n", ranking[i]);

  return 0;
}

void bfs(int R){
  int temp, cur_node;
  
  visited[R] = 1;
  ranking[R] = cur_rank++;
  sort(E[R].begin(), E[R].end());
  
  Q.push(R);

  while(Q.size()){
    temp = Q.front();
    Q.pop();

    for(int i=0; i<E[temp].size(); i++){
      cur_node = E[temp][i];
      
      if(!visited[cur_node]){
        visited[cur_node] = 1;
        ranking[cur_node] = cur_rank++;
        sort(E[cur_node].begin(), E[cur_node].end());
        
        Q.push(cur_node);
      }
    }
  }
}

bfs 문제 찾다가 푼 문제. 24479랑 거의 비슷하고, 그냥 bfs 방식으로 순서 찾는다는 거 말고는 다른 점 없음.
*/