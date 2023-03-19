#include <iostream>
#define MAX 16

using namespace std;

int wall[MAX][MAX];
int dp[3][MAX][MAX];

int DP(int i, int r, int c);

int main(){
  int N, ans = 0;

  scanf("%d", &N);

  for(int r=0; r<N; r++){
    for(int c=0; c<N; c++){
      scanf("%d", &wall[r][c]);
      for(int i=0; i<3; i++)
        dp[i][r][c] = -1;
    }
  }

  for(int i=0; i<3; i++){
    for(int r=0; r<MAX; r++){
      dp[i][r][0] = 0;
      dp[i][r][1] = 0;
    }
  }
  dp[2][0][1] = 1;

  for(int i=0; i<2; i++)
    for(int c=0; c<MAX; c++)
      dp[i][0][c] = 0;

  for(int i=0; i<3; i++)
    ans += DP(i, N-1, N-1);
  
  printf("%d", ans);

  return 0;
}

int DP(int i, int r, int c){
  if(dp[i][r][c] != -1) return dp[i][r][c];

  if(wall[r][c]) return (dp[i][r][c] = 0);

  if(i==0)
    dp[0][r][c] = DP(0, r-1, c) + DP(1, r-1, c);
  else if(i==1){
    if(wall[r-1][c] || wall[r][c-1]) dp[1][r][c] = 0;
    else dp[1][r][c] = DP(0, r-1, c-1) + DP(1, r-1, c-1) + DP(2, r-1, c-1);
  }
  else
    dp[2][r][c] = DP(1, r, c-1) + DP(2, r, c-1);

  return dp[i][r][c];
}