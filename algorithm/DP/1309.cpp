#include <iostream>
#define MAX 100000
#define MOD 9901

using namespace std;

int dp[MAX][3];

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  cin >> N;

  for(int j=0; j<3; j++)
    dp[0][j] = 1;
  
  for(int i=1; i<N; i++){
    dp[i][0] = (dp[i-1][1] + dp[i-1][2])%MOD;
    dp[i][1] = (dp[i-1][0] + dp[i-1][2])%MOD;
    dp[i][2] = (dp[i-1][0] + dp[i-1][1] + dp[i-1][2])%MOD;
  }

  cout << (dp[N-1][0] + dp[N-1][1] + dp[N-1][2])%MOD;

  return 0;
}

/*
기초적인 dp문제.
*/