#include <iostream>
#include <stdlib.h>

using namespace std;

int board[9][9];

void solve(int r, int c); // (r, c)에 수를 알맞은 수를 넣기
bool check(int r, int c, int n); // (r, c)에 n을 넣었을 때 규칙에 맞으면 true
void print_board(void); // 보드를 출력하고 프로그램 종료

int main(){
  string temp;

  for(int i=0; i<9; i++){
    cin >> temp;
    for(int j=0; j<9; j++)
      board[i][j] = temp[j]-'0';
  }

  solve(0, 0);

  return 0;
}

void solve(int r, int c){
  int next_r, next_c;
  next_c = (c==8) ? 0 : c+1;
  next_r = (next_c==0) ? r+1 : r;

  if(board[r][c]){
    if(next_r != 9)
      solve(next_r, next_c);
    else
      print_board();
  }
  else{
    for(int i=1; i<=9; i++){
      if(check(r, c, i)){
        board[r][c] = i;
        if(next_r != 9)
          solve(next_r, next_c);
        else
          print_board();
        board[r][c] = 0;
      }
    }
  }
}

bool check(int r, int c, int n){
  int r_start = (r/3)*3, c_start = (c/3)*3;

  for(int row = r_start; row<r_start+3; row++)
    for(int col = c_start; col<c_start+3; col++)
      if(board[row][col] == n)
        return false;

  for(int row=0; row<9; row++)
    if(board[row][c] == n)
      return false;

  for(int col=0; col<9; col++)
    if(board[r][col] == n)
      return false;
  
  return true;
}

void print_board(void){
  for(int i=0; i<9; i++){
    for(int j=0; j<9; j++)
      printf("%d", board[i][j]);
    printf("\n");
  }
  exit(0);
}

/*
2580과 거의 똑같은 백트래킹 문제. 칸 사이에 공백 없이 입력이 주어진다는 점 빼면 사실상 똑같다. 그때 풀이와 다른 점이라면, 그때는 특정 칸에 
들어있는 수가 규칙에 맞는지 안 맞는지 판단하는 함수를 짰는데, 순서가 1) 특정 칸에 수 넣기. 2) 함수 돌려서 맞는지 판단하기. 였는데
이번에는 특정 빈 칸(0이 입력된)에 n을 넣으면 규칙에 맞는지 안 맞는지 판단하는 함수를 짰고, 순서가 1) n을 인자로 함수 돌리기. 2) 맞다면 
그 빈 칸에 n 넣기. 였다. 그때 풀이는 행 열 3*3칸 을 판단할 때 자기자신 칸은 제외하는 부분이 들어갔었는데 이번 풀이는 그런 부분이 필요가
없어서 빠지게 되었다.
그리고 그때는 0으로 입력된 칸을 벡터에 넣어서 그 좌표만 돌면서 푸는 방식이었는데 이번에는 그냥 모든 칸을 돌면서 빈칸이면 수를 넣는 방식으로
했다. 어쨌든 그때 풀이나 이번 풀이나 별 차이는 없었음
*/