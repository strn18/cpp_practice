#include <iostream>

using namespace std;

int main(){
  int n;
  int dp[1001]={0};
  dp[1] = 1;
  dp[2] = 2;

  scanf("%d", &n);

  for(int i=3; i<=n; i++)
    dp[i] = (dp[i-2]+dp[i-1])%10007;
    
  printf("%d", dp[n]);

  return 0;
}

/*
시간 없어서 간단히 풀어본 쉬운 dp문제. 2*n 직사각형을 채우는 경우는, 맨 왼쪽에 2*1 타일을 놓은 후 오른쪽의 2*(n-1) 직사각형을 채우는 경우의 수와
맨 왼쪽 2*2 공간에 1*2 타일 두개를 위아래로 놓은 후 오른쪽의 2*(n-2) 직사각형을 채우는 경우의 수를 합친 것과 같다.
그러므로, dp[n]: 2*n 직사각형을 채우는 경우의 수일 때, dp[n] = dp[n-1]+dp[n-2]와 같다. 나머지 연산만 해주면 끝
*/