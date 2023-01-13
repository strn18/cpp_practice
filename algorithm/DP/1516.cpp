#include <iostream>

using namespace std;

int dp[501] = {0};
int time[501], pre[501][501];

int DP(int i);

int main(){
  int N;

  scanf("%d", &N);
  for(int i=1; i<=N; i++){
    scanf("%d", &time[i]);

    for(int j=0; 1; j++){
      scanf("%d", &pre[i][j]);      
      if(pre[i][j] == -1) break;
    }
  }

  for(int i=1; i<=N; i++)
    printf("%d\n", DP(i));

  return 0;
}

int DP(int i){
  if(!dp[i]){
    for(int j=0; pre[i][j]!=-1; j++)
      dp[i] = max(dp[i], DP(pre[i][j]));

    dp[i] += time[i];
  }

  return dp[i];
}

/*
1005와 유사하지만, 좀 더 쉬웠던 dp문제. dp[i]: i번 건물을 짓기 위해 드는 최소 시간. 으로 두고, i번 건물의 선행 건물들을 pre[i]에 넣었을 때,
dp[i] = max(pre[i][0], pre[i][1], ...)+time[i]로 점화식을 세웠다. 각 건물 별로 선행 건물 입력의 끝을 나타내는 -1 관련한 처리만 잘 해주면,
점화식 그대로 구현하면 끝이라 어렵지 않았다.
근데 다른 풀이들을 보니, 다들 이 문제를 위상 정렬이라는 개념으로 풀었다. 건물 1의 선행이 2와 3이고, 건물 2의 선행이 4, 건물 3의 선행이 4,
건물 4의 선행은 없을 때, 건물들을 4 2 3 1 이 순서로 정렬하는게 위상 정렬이라고 한다. 나는 그런 거 없이 걍 dp로 때려박아서 풀었는데,
나중에 이거에 대해서 한 번 공부해보면 좋을듯. 1005번 풀 때도 그냥 dp로만 풀었던 것 같은데 ㅋㅋ
*/