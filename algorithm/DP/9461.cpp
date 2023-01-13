#include <iostream>

using namespace std;

int main(){
  int T, N;
  long long dp[101] = {0, 1, 1};

  scanf("%d", &T);

  while(T--){
    scanf("%d", &N);

    for(int i=3; i<=N; i++)
      dp[i] = dp[i-2]+dp[i-3];

    printf("%lld\n", dp[N]);
  }

  return 0;
}

/*
수를 나열하다보면, P(i) = P(i-2)+P(i-3) 이라는 규칙을 어렵지 않게 찾을 수 있다. 다만, i가 커지면서 P(i)도 매우 커지기 때문에 int 형으로는 안 되고
long long 형을 사용해야 함
*/