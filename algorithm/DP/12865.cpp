#include <iostream>
#define MAX_N 100
#define MAX_K 100000

using namespace std;

int dp[MAX_N+1][MAX_K+1] = {0};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, K, W, V;

  cin >> N >> K;

  for(int i=1; i<=N; i++){
    cin >> W >> V;

    for(int j=1; j<=K; j++){
      if(j >= W)
        dp[i][j] = max(dp[i-1][j-W]+V, dp[i-1][j]);
      else
        dp[i][j] = dp[i-1][j];
    }
  }

  cout << dp[N][K];

  return 0;
}

/*
다시 풀어본 0/1 냅색 문제.
*/