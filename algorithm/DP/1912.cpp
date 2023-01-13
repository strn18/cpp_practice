#include <iostream>

using namespace std;

int main(){
  int n, ans;
  int dp[100000], num[100000];

  scanf("%d", &n);

  for(int i=0; i<n; i++)
    scanf("%d", &num[i]);

  dp[0] = num[0];
  for(int i=1; i<n; i++)
    dp[i] = max(dp[i-1]+num[i], num[i]);

  ans = dp[0];
  for(int i=1; i<n; i++)
    ans = max(ans, dp[i]);
  
  printf("%d", ans);

  return 0;
}

/*
아 진짜 짜증나네 왜 자꾸 난이도도 낮은 문제에서 막히냐?

dp[i]: i번째 수까지 봤을 때, 가장 큰 합.으로 두고 풀려 했는데, 별 똥꼬쇼 다 해봤으나 소득 x
그래서 https://mtoc.tistory.com/41 여기 참조함. dp[i]: i번째 수를 골랐을 때, 가장 큰 합.으로 둔 다음, 경우는 1) i-1번째를 골랐던 거를 그대로
이어가기. 2) 끊고, i번째만 고르며 새로 가기. 이 두 가지뿐이니까, dp[i] = max(dp[i-1]+num[i], num[i]) 로 점화식이 나왔다.
그 다음에는 마지막에 dp 테이블 다 돌아보면서 최댓값 구하고 출력하면 됨.

풀이 보면 좃밥인데 한 번 막히면 ㅈㄴ 모르겠네 dp 특이냐?
*/