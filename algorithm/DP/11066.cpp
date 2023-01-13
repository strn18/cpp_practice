#include <iostream>
#include <string.h>

using namespace std;

int file[501];
int dp[501][501];

int merge(int i, int j); // i장~j장을 합치는데 드는 최소비용

int main(){
  int T;
  scanf("%d", &T);

  while(T--){
    int K;
    scanf("%d", &K);

    memset(dp, 0, 501*501*sizeof(int));
    for(int i=1; i<=K; i++)
      scanf("%d", &file[i]);
    printf("%d\n", merge(1, K));
  }

  return 0;
}

int merge(int i, int j){
  if(i!=j && !dp[i][j]){
    int cost = merge(i, i)+merge(i+1, j);
    for(int k=1; k<j-i; k++)
      cost = min(cost, merge(i, i+k)+merge(i+k+1, j)); // 왼쪽 파일을 만드는(왼쪽을 합쳐가는) 비용+오른쪽 파일을 만드는 비용이 최소.

    for(int k=i; k<=j; k++) // 이제 만들어진 왼쪽 파일과 오른쪽 파일을 합치는데 드는 비용을 더해준다.
      cost += file[k]; // 그 비용은 i장~j장의 파일 크기의 합과 같다.

    dp[i][j] = cost;
  }

  return dp[i][j];
}

/*
좀 어려웠던 dp문제. 처음에는 백트래킹으로 푸는 줄 알고, 파일을 합치는 모든 경우를 다 탐색하는 방식으로 짜 보았는데 답은 잘 나왔으나 시간이 너무
오래 걸려서, 예제 2번도 제대로 동작을 안 했다. 사실 그렇게 짜면 시간복잡도가 n!가 되어버리기 때문에 시간초과가 안 날 수가 없다.

이후 도저히 갈피를 못 잡겠어서 https://cocoon1787.tistory.com/317 여기 풀이를 참고했다.
dp[i][j]: i장~j장을 합치는데 필요한 최소비용. 으로 두고,
dp[i][j] = min(dp[i][i]+dp[i+1][j], dp[i][i+1]+dp[i+2][j], ..., dp[i][j-1]+dp[j][j]) 이렇게 점화식을 세웠다.
i==j일 때 dp[i][j]는 0이 되어야 하는데, file[i]로 두는 바람에 값이 틀리게 나왔던 것 이후로는 현재 코드처럼 잘 고쳐서 제출했더니 맞았다.
근데 위 블로그 풀이를 보니까, 내 코드의 34, 35행을 sum이라는 배열을 만들어서 더 짧게 구현한 것을 확인했고, 나도 좀 바꿔서 제출(백준에 있음)하니까
맞았다. 근데 블로그처럼 시간이 많이 짧아질 줄 알았는데 별로 안 줄어들었다..  아마 나는 dp배열 외에 함수를 추가해서 하향식으로 풀었고 블로그는
그냥 dp배열만 채우는 식으로 상향식으로 풀어서, 방식이 좀 달라서 그런듯
*/