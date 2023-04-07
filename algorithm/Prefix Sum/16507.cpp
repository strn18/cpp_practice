#include <iostream>
#define MAX 1000

using namespace std;

int board[MAX+1][MAX+1], sum[MAX+1][MAX+1] = {0};

int rect_average(int r1, int c1, int r2, int c2);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int R, C, Q;
  int r1, c1, r2, c2;

  cin >> R >> C >> Q;

  for(int i=1; i<=R; i++){
    for(int j=1; j<=C; j++){
      cin >> board[i][j];
      sum[i][j] = (sum[i][j-1] + sum[i-1][j] - sum[i-1][j-1]) + board[i][j];
    }
  }

  while(Q--){
    cin >> r1 >> c1 >> r2 >> c2;
    cout << rect_average(r1, c1, r2, c2) << '\n';
  }

  return 0;
}

int rect_average(int r1, int c1, int r2, int c2){
  int dots = (r2-r1+1)*(c2-c1+1);

  return (sum[r2][c2]- sum[r2][c1-1] - sum[r1-1][c2] + sum[r1-1][c1-1])/dots;
}

/*
2차원 구간 합 기본 문제. 첨에는 그냥 제출했다가, 나중에 ios_base 어쩌고 저거 붙이고 cin cout으로 바꾸고 제출했더니 시간 줄었다.
*/