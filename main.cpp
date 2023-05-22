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