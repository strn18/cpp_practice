#include <iostream>
#define MAX 500

using namespace std;

int N;
bool dist[MAX+1][MAX+1] = {false};

bool check(int start);

int main(){
  int M, a, b, count = 0;

  scanf("%d %d", &N, &M);

  for(int i=0; i<M; i++){
    scanf("%d %d", &a, &b);
    dist[a][b] = true;
  }

  for(int k=1; k<=N; k++){
    for(int i=1; i<=N; i++){
      if(!dist[i][k]) continue;

      for(int j=1; j<=N; j++)
        if(dist[k][j])
          dist[i][j] = true;
    }
  }

  for(int i=1; i<=N; i++)
    if(check(i)) count++;

  printf("%d", count);

  return 0;
}

bool check(int start){
  for(int i=1; i<=N; i++){
    if(i==start) continue;
    if(!dist[start][i] && !dist[i][start]) return false;
  }
  
  return true;
}