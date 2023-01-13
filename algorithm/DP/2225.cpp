#include <iostream>
#define MOD 1000000000

using namespace std;

long long dp[201][201] = {0};

long long DP(int i, int j);

int main(){
  int N, K;

  scanf("%d %d", &N, &K);

  printf("%d", DP(K, N));

  return 0;
}

long long DP(int i, int j){
  if(!dp[i][j]){
    if(i==1 || j==0)
      dp[i][j] = 1;

    else
      for(int v=0; v<=j; v++){
        dp[i][j] += DP(1, v)*DP(i-1, j-v);
        dp[i][j] %= MOD;
      }
  }

  return dp[i][j];
}

/*
처음에는 좀 헷갈렸지만 천천히 생각해보니 점화식 떠올릴 수 있었던 문제. dp[i][j] = i개를 사용하여 j를 만드는 경우의 수. 라고 두면,
그 값은 숫자 i개 중에서 제일 왼쪽 숫자가 0일 때 + 1일 때 + 2일 때 + ... + j일 때를 모두 합한 값과 같다.
즉, 제일 왼쪽이 0이고 그 오른쪽들은 합쳐서 j-0일 때 부터, 제일 왼쪽이 j이고 그 오른쪽들은 합쳐서 0일 때의 경우의 수를 모두 구해주면 된다.
즉 dp[i][j] = dp[1][0]+dp[i-1][j] + dp[1][1]+dp[i-1][j-1] + ... + dp[1][j]+dp[i-1][0] 이다.
이때 i가 1일 때는, 숫자 하나로 j를 만드는 경우니까 당연히 그 값은 1이고, j가 0일 때는 숫자를 몇 개를 쓰든 0만 쓰니까 값은 1이다. 
이 두 가지를 base condition으로 해서, DP 함수를 정의하였다. 그리고 10억으로 나누는 나머지 연산 부분까지 추가하니까 맞았다. 참고로
dp값이 최대 10억-1 까지 커질 수 있는데, 이때 27행에서 dp값 두 개를 곱하는 경우가 있기에 int형을 쓴다면 21억을 초과해버려서 안 됨.
그래서 long long형을 썼다.

다 풀고 https://yabmoons.tistory.com/128 여기 풀이 읽으면서 방금 안 건데 점화식에서 dp[1][?] 이 부분은 어차피 i가 1이라 그 값이 1이니까
빼도 된다.. 즉 27행에서 DP(1, v) 이 값은 무조건 1이니까 그거 빼고 그냥 dp[i][j] += DP(i-1, j-v) 이렇게만 해도 됨
*/