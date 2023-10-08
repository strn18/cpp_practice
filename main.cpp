#include <iostream>
#define MAX 50

using namespace std;

int board[MAX][MAX];

bool valCheck(int row, int col, int len);

int main(){
  // ios_base::sync_with_stdio(false);
  // cin.tie(NULL);

  int N, M;

  cin >> N >> M;

  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      scanf("%1d", &board[i][j]);
  
  for(int len = min(N, M); len >= 2; len--){
    for(int row = 0; row + (len-1) < N; row++){
      for(int col = 0; col + (len-1) < M; col++){
        if(valCheck(row, col, len)){
          cout << len * len;
          return 0;
        }
      }
    }
  }

  cout << 1;

  return 0;
}

bool valCheck(int row, int col, int len){
  if(board[row][col] != board[row][col + (len-1)]) return false;
  if(board[row][col] != board[row + (len-1)][col]) return false;
  if(board[row][col] != board[row + (len-1)][col + (len-1)]) return false;
  return true;
}