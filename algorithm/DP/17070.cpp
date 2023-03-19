#include <iostream>
#define MAX 16

using namespace std;

int wall[MAX][MAX];
int dp[3][MAX][MAX];

int DP(int i, int r, int c);

int main(){
  int N, ans = 0;

  scanf("%d", &N);

  for(int r=0; r<N; r++){
    for(int c=0; c<N; c++){
      scanf("%d", &wall[r][c]);
      for(int i=0; i<3; i++)
        dp[i][r][c] = -1;
    }
  }

  for(int i=0; i<3; i++){
    for(int r=0; r<MAX; r++){
      dp[i][r][0] = 0;
      dp[i][r][1] = 0;
    }
  }
  dp[2][0][1] = 1;

  for(int i=0; i<2; i++)
    for(int c=0; c<MAX; c++)
      dp[i][0][c] = 0;

  for(int i=0; i<3; i++)
    ans += DP(i, N-1, N-1);
  
  printf("%d", ans);

  return 0;
}

int DP(int i, int r, int c){
  if(dp[i][r][c] != -1) return dp[i][r][c];

  if(wall[r][c]) return (dp[i][r][c] = 0);

  if(i==0)
    dp[0][r][c] = DP(0, r-1, c) + DP(1, r-1, c);
  else if(i==1){
    if(wall[r-1][c] || wall[r][c-1]) dp[1][r][c] = 0;
    else dp[1][r][c] = DP(0, r-1, c-1) + DP(1, r-1, c-1) + DP(2, r-1, c-1);
  }
  else
    dp[2][r][c] = DP(1, r, c-1) + DP(2, r, c-1);

  return dp[i][r][c];
}

/*
어렵지 않았던 dp문제.
처음에는 dfs로 접근했다. 파이프의 회전 방향과 앞부분의 좌표를 갖고 dfs로 탐색하면서, (N-1, N-1)에 도달하는 경우의 수를 다 세주면 되나? 라고 
생각했는데, 좀 더 생각해보니 더 쉽게 dp로 풀 수 있었음.

dp[i][r][c]: 파이프의 방향이 i이고, 앞부분의 좌표가 (r, c)가 되도록 이동하는 경우의 수. 이다. 이때, i가 0이면 수직, 1이면 대각선, 2이면 수평이다.
이렇게 하면, 50행, 53행, 56행의 점화식(각 i값에 해당하는)을 쉽게 떠올릴 수 있다. 

이제 예외 케이스만 생각해주면 되는데, 우선 c가 0 또는 1일 때는, 딱 하나 빼고 모든 dp값이 반드시 0이다. 앞부분이 (0, 1)이고 수평인 상태로 시작하기
때문에, 앞부분의 위치의 열값이 0이나 1일 수는 없다. 딱 하나 빼고. 바로 dp[2][0][1] 이거임. 얘는 맨 처음 파이프의 상태이기에, 그것만 1로 해준다.
그 다음, r이 0일 때, i값이 0이나 1(수직 또는 대각선)이면 dp값은 0이다. 0행에 파이프의 앞부분을 두고, 수직이나 대각선으로 두면 범위를 초과하기
때문임. 그리고, (r, c)에 벽이 있을 경우도 당연히 dp값은 0이다. 
마지막으로, i=1일 때, (r, c)의 윗칸이나 왼쪽칸에 벽이 있어도 dp값은 0이다(거기가 빈칸이어야 한다고 문제에 써있음). 그렇기에, 52행에서 처리해줌.

이 예외 케이스들만 잘 제외해주면, 나머지는 위의 점화식 그대로 쓰면 된다.
*/