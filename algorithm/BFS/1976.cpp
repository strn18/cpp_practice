#include <iostream>
#include <queue>
#define MAX 200

using namespace std;

int N;
int adj[MAX+1][MAX+1];
int connected[MAX+1] = {0};

void bfs(int start, int n);

int main(){
  int M, count = 0;
  int plan[1000];
  bool flag = true;

  scanf("%d %d", &N, &M);
  for(int i=1; i<=N; i++)
    for(int j=1; j<=N; j++)
      scanf("%d", &adj[i][j]);
  
  for(int i=1; i<=N; i++)
    if(!connected[i])
      bfs(i, ++count);
  
  scanf("%d", &plan[0]);
  for(int i=1; i<M; i++){
    scanf("%d", &plan[i]);
    if(connected[plan[i]] != connected[plan[0]])
      flag = false;
  }

  printf("%s", flag ? "YES" : "NO");

  return 0;
}

void bfs(int start, int n){
  queue<int> q;
  q.push(start);
  connected[start] = n;

  while(!q.empty()){
    int cur = q.front();
    q.pop();

    for(int i=1; i<=N; i++){
      if(adj[cur][i] && !connected[i]){
        q.push(i);
        connected[i] = n;
      }
    }
  }
}

/*
분리집합 문제인데 bfs로 풀어봤다. 
*/