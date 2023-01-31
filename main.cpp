#include <iostream>
#include <string.h>
#define MAX 100
#define DEN 1000000000

using namespace std;

int dp[10][10][MAX+1][10];

int DP(int left, int right, int i, int j);

int main(){
  int N;
  long long count = 0;

  scanf("%d", &N);
  
  memset(dp, -1, 10*10*(MAX+1)*10*sizeof(int));
  
  for(int j=1; j<=9; j++)
    count += DP(0, 9, N, j);

  printf("%lld", count % DEN);

  return 0;
}

int DP(int left, int right, int i, int j){
  if(dp[left][right][i][j] != -1) return dp[left][right][i][j];

  
  if(right<left || (left==right && i>1) || right-left+1>i || j<left || right<j || i==0){
    dp[left][right][i][j] = 0;
    return dp[left][right][i][j];
  }
  else if(right-left+1==i){
    if(j==left || j==right) dp[left][right][i][j] = 1;
    else dp[left][right][i][j] = 0;
    return dp[left][right][i][j];
  }
  

  if(left<j && j<right){
    dp[left][right][i][j] = DP(left, right, i-1, j-1) + DP(left, right, i-1, j+1);
  }
  else if(j == left){
    dp[left][right][i][j] = DP(left+1, right, i-1, j+1) + DP(left, right, i-1, j+1);
  }
  else{
    dp[left][right][i][j] = DP(left, right-1, i-1, j-1) + DP(left, right, i-1, j-1);
  }

  dp[left][right][i][j] %= DEN;

  return dp[left][right][i][j];
}