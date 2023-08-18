#include <iostream>
#define MAX 100

using namespace std;

int board[MAX][MAX];
long long dp[MAX][MAX];

long long DP(int r, int c);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  cin >> N;

  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      cin >> board[i][j];
      dp[i][j] = -1;
    }
  }

  dp[0][0] = 1;

  cout << DP(N-1, N-1);

  return 0;
}

long long DP(int r, int c){
  if(dp[r][c] != -1) return dp[r][c];

  long long count = 0;

  for(int i=0; i<r; i++)
    if(board[i][c] == r-i) count += DP(i, c);
  
  for(int j=0; j<c; j++)
    if(board[r][j] == c-j) count += DP(r, j);
  
  return dp[r][c] = count;
}

/*
어렵지 않았던 dp 문제. 처음에는 그냥 하나하나 다 세면 되나 했는데 경로의 수가 2^63 - 1 이하라서 시간초과 남.

그래서 dp로 풀었다. dp[i][j]: (i, j)로 도달하는 경로의 수. 로 둔 다음, 어떤 칸의 dp 값이 비었다면 그 칸의 왼쪽 칸들과 위쪽 칸들을 보고, 
걔네들한테 적힌 값(board의 값)과 어떤 칸과의 거리가 같다면, 걔네들의 dp 값을 더해주면 된다.
*/