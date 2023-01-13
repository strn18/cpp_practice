/*
#include <iostream>
#include <vector>

using namespace std;

int total = -1; 
int infected[101] = {0};
vector<int> connect[101];

void dfs(int v);

int main(){
  int N, E;
  int v1, v2;
  
  scanf("%d", &N);
  scanf("%d", &E);

  for(int i=0; i<E; i++){
    scanf("%d %d", &v1, &v2);
    connect[v1].push_back(v2);
    connect[v2].push_back(v1);
  }

  dfs(1);

  printf("%d", total);

  return 0;
}

void dfs(int v){
  infected[v] = 1;
  total++;

  for(int i=0; i<connect[v].size(); i++){
    int next = connect[v][i];
    if(!infected[next])
      dfs(next);
  }
}

쉬운 dfs/bfs 문제였고 빨리 풀었다. 2667처럼 dfs나 bfs나 뭘로 풀든 상관 없는 문제였는데 dfs로 풀었음. 진짜 그냥 기본적인 문제였는데, 풀다가 느낀건데 bfs보다 dfs가 코드 짜는게 훨씬 빠르고 간편한 것 같다.
*/