#include <iostream>
#define MAX 400

using namespace std;

bool relate[MAX+1][MAX+1] = {false};

int main(){
  int N, K, S, first, next;

  scanf("%d %d", &N, &K);
  for(int i=0; i<K; i++){
    scanf("%d %d", &first, &next);
    relate[first][next] = true;
  }

  for(int k=1; k<=N; k++){
    for(int i=1; i<=N; i++){
      if(!relate[i][k]) continue;

      for(int j=1; j<=N; j++){
        if(!relate[k][j] || i==j) continue;
        
        relate[i][j] = true;
      }
    }
  }

  scanf("%d", &S);
  for(int i=0; i<S; i++){
    scanf("%d %d", &first, &next);

    if(relate[first][next])
      printf("-1\n");
    else if(relate[next][first])
      printf("1\n");
    else
      printf("0\n");
  }

  return 0;
}