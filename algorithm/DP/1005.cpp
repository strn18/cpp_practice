#include <iostream>
#include <string.h>

using namespace std;

int N;
int time[1001], dp[1001], found[1001]; // i번 건물 건설 시간, i번 건물을 짓는데 드는 최소 시간, dp[i]를 찾았는지 여부
int rule[1001][1001]; // rule[i][j] = 1이라면, i번 건물을 짓기 위해 j번 건물을 지어야함을 의미

int DP(int n);

int main(){
  int T;
  scanf("%d", &T);

  while(T--){
    int K, a, b, W;

    memset(dp, 0, 1001*sizeof(int));
    memset(found, 0, 1001*sizeof(int));
    memset(rule, 0, 1001*1001*sizeof(int));
    
    scanf("%d %d", &N, &K);

    for(int i=1; i<=N; i++)
      scanf("%d", &time[i]);

    for(int i=0; i<K; i++){
      scanf("%d %d", &a, &b);
      rule[b][a] = 1;
    }

    scanf("%d", &W);

    printf("%d\n", DP(W));
  }

  return 0;
}

int DP(int n){
  if(!found[n]){
    int cost = 0;

    for(int i=1; i<=N; i++)
      if(rule[n][i])
        cost = max(cost, DP(i));

    cost += time[n];
    dp[n] = cost;
    found[n] = 1;
  }
  return dp[n];
}

/*
코드 짜는 건 쉬웠는데 자꾸 메모리초과&시간초과가 나서 좃같았던 dp 문제.
dp[i]는 i번 건물을 짓는데 드는 최소 시간이고, rule[a][b]가 1이라면 a번 건물을 짓기 위해 b번 건물을 지어야한다는 것을 뜻할 때,
rule[i][j] = 1을 만족하는 j가 (a, b, c)일 때, dp[i] = max(dp[a], dp[b], dp[c]) + time[i]이다(time[i]는 i번 건물의 건설 시간).
이 점화식을 떠올리는 건 쉬웠고 코드 짜는 것도 어렵지 않았다. 근데 처음에는 rule을 2차원 배열이 아니라 벡터 배열로 만들었고,
vector<int> rule[1001]로 하여, i번 건물을 짓기 위해 필요한 건물 번호들을 rule[i]에 push_back 해주는 식으로 했다.

그런데 왜인지는 모르겠는데 메모리초과가 발생했다. 규칙은 최대 10만개라서 rule의 크기는 끽해야 4(int의 크기)*10만 바이트 정도라고 생각했는데,
왜 메모리초과가 되는지 알 수 없었음. 

고민 좀 해보다가 모르겠어서 걍 벡터가 아니라 2차원 배열을 사용했다. 근데 그때는 found 배열을 사용 안 한 상태였고 42행이 if(!dp[n])이었다.
즉, dp값이 0이라면 아직 dp값을 못 찾은 것으로 본다는 것인데, 문제를 보면 건설 시간은 0이 될 수 있기 때문에, dp값도 0이 될 수 있다(i번
건물을 짓기 위해 필요한 건물들의 건설 시간이 0이고 i번 건물의 건설 시간도 0이면 dp[i]는 0임). 이렇게 되면, dp값은 0으로 이미 찾았는데, if(!dp[n])
때문에 dp값을 못 찾은 줄 알고 밑의 부분을 쓸데없이 반복 실행하게 된다. 
이거 때문에 2차원 배열 사용한 코드 제출에서 시간초과가 났고, 지금 코드처럼 found 배열을 사용하여 dp값을 찾았는지 체크해주니 맞았다고 떴다.

근데 그거 제출하기 전에, 혹시나 해서 벡터 쓴 코드에 found 배열만 추가하여 제출해봤는데 그것도 메모리초과가 남. 왜 나는지 모르겠다;;
*알고보니, rule[i] = vector<int>() 이걸로 rule을 비워주는 부분에서, i를 [1, N]으로 해줘야하는데 [0, N)으로 해주는 바람에 rule[N]이 비워지지
않았고, 이거 때문에 다음 테스트케이스 때 사이클이 이뤄지게 되어서 재귀 무한호출이 일어난 것이었다.. 이 부분 고치고 제출하니 맞았음
*/