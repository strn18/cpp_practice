#include <iostream>
#define MAX 1000
#define DEN 1000000003

using namespace std;

int dp[MAX+1][MAX+1] = {0}; // dp[i][j]: 0~i번 색 중에서 j개 고르기

int main(){
  int N, K;

  scanf("%d", &N);
  scanf("%d", &K);

  for(int i=0; i<=N; i++){
    dp[i][0] = 1;
    dp[i][1] = i;
  }

  for(int i=2; i<=N; i++)
    for(int j=2; (j<=K && j<=i); j++)
      dp[i][j] = (dp[i-2][j-1] + dp[i-1][j]) % DEN; // i번 색을 고를 경우 + i번 색을 안 고를 경우

  printf("%d", (dp[N-3][K-1] + dp[N-1][K]) % DEN); // 0번 색을 고를 경우 + 0번 색을 안 고를 경우

  return 0;
}