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

/*
쉬운 콤비네이션(조합) 구하기 dp 문제. 근데 마지막에 쫌 헤맸는데, nCr 에서 r이 0이면 값은 1이 되어야 하는데(n개 중에 0개를 고르는 가짓수는 
아무 것도 안 고르기 라는 딱 한 가지니까), 0이라고 생각해서 틀렸다.
*/