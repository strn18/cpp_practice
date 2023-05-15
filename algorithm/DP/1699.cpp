#include <iostream>
#define MAX 100000

using namespace std;

int dp[MAX+1] = {0};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  cin >> N;

  for(int i=1; i<=N; i++){
    int minimum = i;

    for(int j=1; j*j<=i; j++)
      minimum = min(minimum, 1+dp[i-(j*j)]);

    dp[i] = minimum;
  }

  cout << dp[N];

  return 0;
}

/*
ㅈ.ㄴ 어려웠던 실버2 문제.. 

처음에는 걍 제일 큰 제곱수부터 그리디하게 하면 되나 했는데 12 같은 반례가 있었다. 9+1+1+1 보다 4+4+4가 항이 적음.

그래서 그 담에는 dp로 풀었음. dp[i]: i를 제곱수의 합으로 표현할 때 항의 최소 개수. 로 놓고 풀었는데, dp[1]+dp[i-1], dp[2]+dp[i-2], ...
를 다 해보고 그 중 min을 dp[i]에 넣는 식이라 시간초과가 났음.

그래서 dfs도 해보고 별 ㅈㄹ 다했는데 안 풀렸다. 그러다가 문득 dp[i]를 구하려면, i 이하인 제곱수를 a, b, c, ...라고 할 때,
dp[a]+dp[i-a], dp[b]+dp[i-b], ... 이것의 min을 구하면 되지 않나? 라는 생각이 들었음. 그래서 그런 식으로 dp를 바꿔서 풀었더니 맞았다.

그러다가 https://lmcoa15.tistory.com/43 여기 보고 좀 더 간략화해서 수정한 게 이 코드(마지막 제출).
*/