#include <iostream>
#define MAX 100000
#define MOD 1000000009

using namespace std;

int dp[MAX+1][4] = {0};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  dp[1][1] = 1;
  dp[2][2] = 1;
  dp[3][1] = 1;
  dp[3][2] = 1;
  dp[3][3] = 1;

  for(int i=4; i<=MAX; i++){
    for(int j=1; j<=3; j++){
      for(int k=1; k<=3; k++){
        if(j != k) dp[i][j] = (dp[i][j] + dp[i-j][k]) % MOD;
      }
    } 
  }
  
  while(T--){
    int n, ans = 0;

    cin >> n;

    for(int j=1; j<=3; j++)
      ans = (ans + dp[n][j]) % MOD;
    
    cout << ans << '\n';
  }

  return 0;
}

/*
쉬운 DP 문제. dp[i][j]: i를 1, 2, 3으로 표현할 때, 마지막 수가 j인 방법의 수.
이때,
dp[i][1] = dp[i-1][2] + d[i-1][3]
dp[i][2] = dp[i-1][1] + d[i-1][3]
dp[i][3] = dp[i-1][1] + d[i-1][2]
이다. 이를 이용하면 쉽게 풀 수 있다. 
*/