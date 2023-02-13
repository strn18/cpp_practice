#include <iostream>
#define MAX 100

using namespace std;

int main(){
  int N;
  int dist[MAX][MAX];

  scanf("%d", &N);
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      scanf("%d", &dist[i][j]);

  for(int k=0; k<N; k++){
    for(int i=0; i<N; i++){
      if(dist[i][k] == 0) continue;
      for(int j=0; j<N; j++){
        if(dist[k][j] == 0) continue;
        dist[i][j] = 1;
      }
    }
  }

  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++)
      printf("%d ", dist[i][j]);
    printf("\n");  
  }

  return 0;
}

/*
쉬웠던 플로이드-와샬 문제. 사실 dfs로 풀어도 된다. https://blog.naver.com/kks227/220797649276 여기 링크에서는 정석적인 플로이드-와샬을
풀 때처럼, i에서 j로 갈 수 없으면(입력이 0이면) INF값을 넣어놓고 플로이드 와샬 방식을 그대로 써서 풀었는데, 나는 입력값 그대로 그냥 사용하고
대신 17행과 19행에서 dist[i][k]와 dist[k][j] 중 하나라도 0이라면(i에서 k를 거쳐 j로 가야하는데, 둘 중 하나라도 경로가 없다면) continue를
쳐주고, 둘 다 1일 때만 20행으로 와서 i에서 j로 가는 경로가 있다(값이 1)고 표시해주는 것으로 했다.
*/