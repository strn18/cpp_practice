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

/*
걍 브루트포스로 모든 정사각형을 다 찾아보면 된다. 그러면 O(N^3)인데, N이 작아서 충분히 가능. 
꼭짓점의 수가 같은 가장 큰 정사각형의 넓이를 구하는 거니까, 정사각형의 한 변의 길이를 min(N, M)부터 시작해서 1씩 줄이면서 
그걸 만족하는 정사각형이 있는지 찾아본다. 길이 2까지 찾아봤는데 없으면 길이 1에서는 무조건 있으니까 바로 1을 출력한다. 
*/