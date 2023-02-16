#include <iostream>
#include <queue>
#include <algorithm>
#define MAX 100
#define INF 2100000000

using namespace std;

int N;
int dist[MAX+1][MAX+1];
int group[MAX+1] = {0};

void bfs(int start, int num);

int main(){
  int M, a, b, groups = 0;
  int rep_num[MAX+1], rep_time[MAX+1];

  scanf("%d %d", &N, &M);

  for(int i=1; i<=N; i++)
    for(int j=1; j<=N; j++)
      dist[i][j] = (i==j ? 0 : INF);

  for(int i=0; i<M; i++){
    scanf("%d %d", &a, &b);
    dist[a][b] = 1;
    dist[b][a] = 1;
  }

  for(int i=1; i<=N; i++)
    if(group[i]==0)
      bfs(i, ++groups);

  for(int k=1; k<=N; k++){
    for(int i=1; i<=N; i++){
      if(dist[i][k] == INF) continue;
      for(int j=1; j<=N; j++){
        if(dist[k][j] == INF) continue;
        dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
      }
    }
  }

  for(int i=1; i<=groups; i++)
    rep_time[i] = INF;

  for(int i=1; i<=N; i++){
    int time = 0, group_num = group[i];

    for(int j=1; j<=N; j++)
      if(group[j] == group_num)
        time += dist[i][j];

    if(time < rep_time[group_num]){
      rep_num[group_num] = i;
      rep_time[group_num] = time;
    }
  }

  printf("%d\n", groups);

  sort(rep_num+1, rep_num+1+groups);

  for(int i=1; i<=groups; i++)
    printf("%d\n", rep_num[i]);

  return 0;
}

void bfs(int start, int num){
  queue<int> q;
  q.push(start);
  group[start] = num;

  while(!q.empty()){
    int cur = q.front();
    q.pop();

    for(int i=1; i<=N; i++){
      if(group[i]==0 && dist[cur][i]==1){
        q.push(i);
        group[i] = num;
      }
    }
  }
}