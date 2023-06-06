#include <iostream>
#define MAX 90

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int n;
  long long dp[MAX+1];

  cin >> n;

  dp[0] = 0;
  dp[1] = 1;

  for(int i=2; i<=n; i++)
    dp[i] = dp[i-2] + dp[i-1];

  cout << dp[n];

  return 0;
}