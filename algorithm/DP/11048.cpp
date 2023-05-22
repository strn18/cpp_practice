#include <iostream>
#define MAX 1000

using namespace std;

int board[MAX+1][MAX+1];
int dp[MAX+1][MAX+1] = {0};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;

  cin >> N >> M;

  for(int i=1; i<=N; i++){
    for(int j=1; j<=M; j++){
      cin >> board[i][j];
      dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + board[i][j];
    }
  }

  cout << dp[N][M];  

  return 0;
}

/*
dfs인 줄 알았는데 시간초과 났음. 알고 보니 dp였다. dp[i][j]: (i, j)까지 이동할 때 최대로 먹을 수 있는 사탕 개수. 로 정의하였음.
dp랑 board를 1-based 배열로 썼는데, 모서리 부분이면 예외처리를 해줘야하는데 귀찮아서 1-based로 한 다음에 행이나 열이 0인 칸은 board 값을 0으로 
두었다. 이렇게 하면 dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + board[i][j] 이 점화식으로 다 풀림.

이 문제엔 함정이 있었는데 우하단 대각선으로 이동하는 걸 고려할 필요가 없음. 왜냐? 우하단으로 갈 바엔 우->하 로 가든가 그 반대로 가면 우하단으로
바로 가는 것보다 사탕을 그 이상으로 먹을테니, 우랑 하로 가는 것만 고려하면 되었다.
*/