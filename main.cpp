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