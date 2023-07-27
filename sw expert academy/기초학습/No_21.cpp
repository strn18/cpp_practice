// 0/1 Knapsack(6. DP)
#include <iostream>
#define MAX_N 100
#define MAX_K 1000

using namespace std;

int main(){
  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    int N, K;
    int V[MAX_N], C[MAX_N];
    int dp[MAX_K+1] = {0};

    cin >> N >> K;

    for(int i=0; i<N; i++){
      cin >> V[i] >> C[i];

      for(int j=K; j>=V[i]; j--)
        dp[j] = max(dp[j], dp[j-V[i]] + C[i]);
    }

    cout << '#' << t << ' ' << dp[K] << '\n';
  }

  return 0;
}

/*
이거도 그냥 기초 0/1 냅색 문제.
*/