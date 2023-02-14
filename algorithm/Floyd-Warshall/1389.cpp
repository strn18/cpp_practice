#include <iostream>
#define MAX 100
#define INF 2100000000

using namespace std;

int main(){
  int N, M, A, B;
  int min_bacon, min_num, bacon_count;
  int bacon[MAX+1][MAX+1];

  scanf("%d %d", &N, &M);

  for(int i=1; i<=N; i++)
    for(int j=1; j<=N; j++)
      bacon[i][j] = (i==j ? 0 : INF);

  for(int i=0; i<M; i++){
    scanf("%d %d", &A, &B);
    bacon[A][B] = 1;
    bacon[B][A] = 1;
  }

  for(int k=1; k<=N; k++){
    for(int i=1; i<=N; i++){
      if(bacon[i][k] == INF) continue;
      for(int j=1; j<=N; j++){
        if(bacon[k][j] == INF) continue;
        bacon[i][j] = min(bacon[i][j], bacon[i][k] + bacon[k][j]);
      }
    }
  }

  min_bacon = INF;
  for(int i=1; i<=N; i++){
    bacon_count = 0;

    for(int j=1; j<=N; j++)
      bacon_count += bacon[i][j];

    if(bacon_count < min_bacon){
      min_bacon = bacon_count;
      min_num = i;
    }
  }

  printf("%d", min_num);

  return 0;
}

/*
쉬웠던 플로이드-와샬 문제. 다른 정점으로 가는 거리의 합이 제일 작은 정점의 번호를 출력해주면 된다. bfs로도 한 번 풀어보았음.
*/