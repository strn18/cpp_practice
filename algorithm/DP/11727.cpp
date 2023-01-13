#include <iostream>
#define MAX 1000

using namespace std;

int main(){
  int n;
  int dp[MAX+1];

  scanf("%d", &n);

  dp[0] = 1;
  dp[1] = 1;

  for(int i=2; i<=n; i++){
    dp[i] = (dp[i-1] + 2*dp[i-2])%10007;
  }

  printf("%d", dp[n]);
  
  return 0;
}

/*
시간 없어서 풀었던, 쉬운 dp문제. 11726과 거의 유사하지만, dp[i-2]의 2배를 더해줘야한다는 점만 다르다.
왜냐하면, 2*i 타일을 채우는 가짓수는 1) 맨 오른쪽 2*1을 채울 경우, 그 왼쪽은 2*(i-1)이므로, 가짓수는 dp[i-1]. 2) 맨 오른쪽 2*2를 1*2 두 개로
채울 경우, 그 왼쪽은 2*(i-2)이므로, 가짓수는 dp[i-2]. 3) 맨 오른쪽 2*2를 2*2 한 개로 채울 경우, 똑같이 가짓수는 dp[i-2].
이기 때문에, dp[i-2]를 두 번 세어야한다.
*/