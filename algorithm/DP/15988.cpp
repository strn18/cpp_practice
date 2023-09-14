#include <iostream>
#define MAX 1000000
#define MOD 1000000009

using namespace std;

long long dp[MAX+1];

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  dp[1] = 1;
  dp[2] = 2;
  dp[3] = 4;

  for(int i=4; i<=MAX; i++)
    dp[i] = (dp[i-1] + dp[i-2] + dp[i-3]) % MOD;

  while(T--){
    int n;

    cin >> n;

    cout << dp[n] << endl;
  }

  return 0;
}