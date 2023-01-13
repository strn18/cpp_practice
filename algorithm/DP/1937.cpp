#include <iostream>

using namespace std;

int N;
int bamboo[500][500], dp[500][500] = {0};
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int DP(int r, int c);

int main(){
  int ans = -1;
  
  scanf("%d", &N);
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      scanf("%d", &bamboo[i][j]);

  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      ans = max(ans, DP(i, j));

  printf("%d", ans);

  return 0;
}

int DP(int r, int c){
  if(!dp[r][c]){
    for(int i=0; i<4; i++){
      int R = r+dr[i];
      int C = c+dc[i];

      if(0<=R&&R<N && 0<=C&&C<N && bamboo[R][C]<bamboo[r][c])
        dp[r][c] = max(dp[r][c], DP(R, C));
    }
    dp[r][c]++;
  }
  return dp[r][c];
}

/*
어렵지 않았던 dp문제. 1520과 매우 유사한 문제였다. dp[i][j]: (i, j)에 왔을 때, 지금까지 이동한 칸(현재 칸 포함) 수의 최댓값.으로 두고,
dp[i][j] = max(상하좌우 중 bamboo값이 현재 칸보다 작은 칸의 dp값) + 1 로 잡으면 된다. 38행에서 +1 해주는 부분을 37행의 중괄호 안에 넣는 바람에
쪼금 버벅거렸던 것 빼면 크게 막히는 부분은 없었다.
*/