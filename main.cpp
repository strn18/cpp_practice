#include <iostream>
#define MAX 1000
#define MOD 10007

using namespace std;

int dp[MAX+1][MAX+1] = {0};

int combination(int n, int r);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, K;

  cin >> N >> K;

  cout << (K==0 ? 1 : combination(N, K));

  return 0;
}

int combination(int n, int r){
  if(dp[n][r]) return dp[n][r];

  if(n==r) return dp[n][r] = 1;
  if(r==1) return dp[n][r] = n;

  return dp[n][r] = (combination(n-1, r)+combination(n-1, r-1))%MOD;
}