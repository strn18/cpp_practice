#include <iostream>
#define INF 2100000000

using namespace std;

int main(){
  int n, k;
  int c[100], dp[10001];
  
  scanf("%d %d", &n, &k);
  for(int i=0; i<n; i++)
    scanf("%d", &c[i]);

  dp[0] = 0;
  for(int i=1; i<=k; i++){
    dp[i] = INF;

    for(int j=0; j<n; j++)
      if(i-c[j]>=0 && dp[i-c[j]]!=-1)
        dp[i] = min(dp[i], dp[i-c[j]]);

    if(dp[i] != INF)
      dp[i]++;
    else
      dp[i] = -1;
  }
  
  printf("%d", dp[k]);

  return 0;
}

/*
2293과 거의 유사했던 dp문제. 가치가 같은 동전이 여러 개 주어질 수 있다는 조건을 제외하면 문제가 똑같았다. 근데 그걸로 뭐 차이가 많이 생기는 건 
아니라, 불가능한 경우에 -1을 출력하는 것을 제외하면 코드는 거의 똑같다. 

저번에는 점화식 찾다가 어려워서 다른 코드 참고하고 풀었는데 이번에는 직접 풀었다. dp[i]: i원을 만드는 데 드는 동전의 최소 개수.로 두고,
dp[i] = min(dp[i-c[0]], dp[i-c[1]], ..., dp[i-c[n-1]])+1 이라는 점화식이 나왔다. i원을 만드려면, (i-'어떠한 동전'의 가치)원을 만드는 데 드는
동전의 개수에, 1만 더해주면 되니까((i-'어떠한 동전'의 가치)원에다가 어떠한 동전 하나를 더하면 되는 거니까), dp[i]는 dp[i-c[j]]+1이 되고, 
이때 이걸 최소로 만드는 c[j]를 찾으면 되는 것이다. 다시 말해, 1원, 2원, 5원이 있을 때, 6원을 만드는 데 드는 동전의 최소 개수를 구하고 싶다면,
5원을 만들 때 최소 개수+1(1원 더하기), 4원을 만들 때 최소 개수+1(2원 더하기), 1원을 만들 때 최소 개수+1(5원 더하기) 중에서 최소를 구해주면 된다. 
dp[5] = 1, dp[4] = 2, dp[1] = 1이니까 답은 2임(동전 구성은 1원 1개, 5원 1개가 되겠지).

이 점화식을 통해, i가 1부터 k일 때(dp[0] = 0이다) dp[i]를 돌고, 그 안에서 c[j]를 돌면서 dp[i]의 최솟값을 찾아주었다. 만약 적절한 c[j]를 찾지
못 했다면(19행을 만족하는 c[j]가 하나도 없었다면), i원을 만들 수 없는 것이니까 -1을 넣어주었다.
*/