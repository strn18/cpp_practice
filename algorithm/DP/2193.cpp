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

/*
처음에는 dp 없이 그냥 풀다가 시간초과 나는 것 같아서 dp 쓴 문제. 

dp[i][0]: 0으로 시작하는(원래는 시작 못하지만 할 수 있다고 가정) i자리 이친수 개수
dp[i][1]: 1로 시작하는 i자리 이친수 개수
라고 두었을 때, dp[i][0]은 i-1자리 이친수(0으로 시작하든 1로 시작하든) 앞에 0 붙이면 되니까 그 개수의 합과 같고,
dp[i][1]은 0으로 시작하는 i-1자리 이친수 앞에 1을 붙어야 한다(1 두 개가 연속이면 안 됨). 그래서 그 개수와 같다.

https://guiyum.tistory.com/15 여기를 보니까 더 간단하게 푸는 방법이 있었음.

*/