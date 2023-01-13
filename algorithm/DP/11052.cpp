#include <iostream>

using namespace std;

int main(){
  int N;
  int P[10001], dp[10001];
  
  scanf("%d", &N);
  
  for(int i=1; i<=N; i++){
    scanf("%d", &P[i]);
    dp[i] = P[i];
    for(int j=1; j<=i/2; j++)
      dp[i] = max(dp[i], dp[j]+dp[i-j]);
  }

  printf("%d", dp[N]);

  return 0;
}

/*
알고리즘 분류 안 보고 풀어서 뭔가했는데 알고보니 쉬웠던 dp문제. 처음에는 P_n이 v일 때, v/n을 해준 값(그 카드팩에서, 카드 1장에 드는 비용)들을
모두 비교한 다음 높은 거 고르고 그 다음 고를 수 있는 것들 중 또 높은 거 고르고... 처럼 그리디인가 했는데 조금 생각해보니 금방 반례가 나왔다.
그래서 좀 고민했더니, 그냥 dp로 dp[i] = max(P[i], dp[i-1]+dp[1], dp[i-2]+dp[2], ...)를 해주면 되는 것이었음.
*/