#include <iostream>
#define MAX 90

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int N;
  long long dp[MAX+1][2] = {0};

  cin >> N;

  dp[1][0] = 1;
  dp[1][1] = 1;

  for(int i=2; i<=N; i++){
    dp[i][0] = dp[i-1][0] + dp[i-1][1];
    dp[i][1] = dp[i-1][0];
  }

  cout << dp[N][1];

  return 0;
}