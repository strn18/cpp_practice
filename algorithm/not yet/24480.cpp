/*
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int visited[100001] = {0};
vector<int> E[100001];

int cur_rank = 1;
int ranking[100001] = {0};

void dfs(int R);

bool compare(int a, int b);

int main(){
  int N, M, R, u, v;
  scanf("%d %d %d", &N, &M, &R);

  for(int i=0; i<M; i++){
    cin >> u >> v;
    E[u].push_back(v);    
    if(u!=v)
      E[v].push_back(u);    
  }

  dfs(R);

  for(int i=1; i<=N; i++)
    printf("%d\n", ranking[i]);

  return 0;
}

void dfs(int R){
  visited[R] = 1;
  sort(E[R].begin(), E[R].end(), compare);
  ranking[R] = cur_rank++;

  for(int i=0; i<E[R].size(); i++)
    if(!visited[E[R][i]])
      dfs(E[R][i]);
}

bool compare(int a, int b){
  return a>b;
}

24479랑 거의 비슷한 문제. 오름차순이 아니라 내림차순으로 탐색하는 거 말곤 다른 거 없음. compare 함수 만들어서 sort에 인자 넘겨주는 식으로 풀었다.
*/