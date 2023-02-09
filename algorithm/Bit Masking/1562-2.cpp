#include <iostream>
#define MAX 100
#define MOD 1000000000

using namespace std;

int dp[MAX+1][10][1<<10] = {0}; // dp[i][j][k]: i번째 수가 j이고, k가 사용한 수를 나타낼 때, 계단 수의 개수

int main(){
  int N, count = 0, full = (1<<10) - 1;

  scanf("%d", &N);

  for(int j=1; j<=9; j++)
    dp[1][j][1<<j] = 1;

  for(int i=2; i<=N; i++){
    for(int j=0; j<=9; j++){
      for(int k=0; k<=full; k++){
        if(j==0)
          dp[i][j][k | (1<<j)] += dp[i-1][1][k];

        else if(j==9)
          dp[i][j][k | (1<<j)] += dp[i-1][8][k];
          
        else
          dp[i][j][k | (1<<j)] += dp[i-1][j-1][k] + dp[i-1][j+1][k];

        dp[i][j][k | (1<<j)] %= MOD;
      }
    }
  }

  for(int j=0; j<=9; j++)
    count = (count + dp[N][j][full]) % MOD;

  printf("%d", count);

  return 0;
}

/*
비트마스킹을 통해 다시 한 번 풀어본 1562번 문제. 자세한 풀이는 https://melonicedlatte.com/algorithm/2018/03/15/160637.html 여기를 참고했다.

간단히 설명하자면, dp[i][j][k]: i번째 수가 j이며, k가 사용한 수를 나타낼 때, 계단 수의 개수. 이다. 이때 k가 사용한 수를 나타낸다는 것은,
k를 비트마스킹 방식으로 사용하여, k의 비트가 1001011010 이렇다면, 1, 3, 4, 6, 9를 사용했다는 뜻이다. 즉 i번째 비트가 1이면, i를 사용했다는
것임. 이 dp를 바텀업 방식으로 채운 다음에, dp[N][j][full]에서 j가 0~9일 때 값을 모두 합쳐주면 된다. full은 비트가 1111111111인 수, 즉
(1<<10) - 1 == 2^10 -1 이다. 다시 말해, 0부터 9까지 모든 수를 사용하였을 때, N번째 수가 0~9인 경우를 모두 더해서 답을 구하는 것임.

자세한 설명은 링크에 있음
*/