/*
#include <iostream>
#include <vector>

using namespace std;

int sudoku[9][9];
vector<pair<int, int>> empty_box; // 빈 칸의 좌표를 넣는 벡터

void Solve(int idx, int r, int c);
int Right(int row, int col); // (row, col)의 값이 올바른지 판별
void Print(); // 스도쿠 출력

int main(){
  for(int i=0; i<9; i++){
    for(int j=0; j<9; j++){
      cin >> sudoku[i][j];
      if(!sudoku[i][j]){ // 입력이 0(빈 칸)이면 벡터에 푸시
        empty_box.push_back(make_pair(i, j));
      }
    }
  }
  Solve(0, empty_box[0].first, empty_box[0].second); // 0번째 빈 칸부터 풀기
}

void Solve(int idx, int r, int c){
  if(idx == empty_box.size()-1){ // 이번 칸이 마지막 빈 칸일 때
    for(int i=1; i<=9; i++){
      sudoku[r][c] = i;
      if(Right(r, c)){ // 맞는 수를 찾으면 출력하고 종료
        Print();
        exit(0);
      }
    }
    sudoku[r][c] = 0; // 못 찾았으면 다시 0 넣어주고 되돌아가기
    return;
  }

  for(int i=1; i<=9; i++){
    sudoku[r][c] = i;
    if(Right(r, c)) // 맞는 수를 찾으면 다음 빈 칸으로 이동
      Solve(idx+1, empty_box[idx+1].first, empty_box[idx+1].second);
  }  
  sudoku[r][c] = 0; // 다시 0 넣어주고 되돌아가기
  return;
}

int Right(int row, int col){  
  for(int c=0; c<9; c++){ // 현재 칸의 가로줄에 같은 게 있는지 판별(같은 칸이거나 빈 칸이면 패스)
    if(c==col || !sudoku[row][c]) continue;
    if(sudoku[row][c]==sudoku[row][col])
      return 0;
  }

  for(int r=0; r<9; r++){ // 현재 칸의 세로줄에 ~~
    if(r==row || !sudoku[r][col]) continue;
    if(sudoku[r][col]==sudoku[row][col])
      return 0;
  }

  for(int r=(row/3)*3; r<(row/3)*3+3; r++){ // 현재 칸의 3*3 정사각형에 ~~
    for(int c=(col/3)*3; c<(col/3)*3+3; c++){
      if((r==row && c==col) || !sudoku[r][c]) continue;
      if(sudoku[r][c]==sudoku[row][col])
        return 0;
    }
  }

  return 1;
}

void Print(){
  for(int i=0; i<9; i++){
    for(int j=0; j<9; j++)
      cout << sudoku[i][j] << ' ';
    cout << endl;
  }
}

백트래킹 문제 중에서 찾아 푼 문제. 20년도 1학기에 컴프1 과제로 풀었던 거랑 비슷한 문제였음. 처음에는 Right 함수가 인자 없이 9*9 스도쿠 판을 
모두 체크하며 틀린 게 있는지 판단하는 역할을 하도록 짜고 제출했는데, 첫 제출에서 컴파일 에러가 났음. 원래 empty_box가 아니라 empty로 벡터 이름을 
설정했는데 empty라는 함수가 std에 내장되어 있는거라 겹처서 ambiguous 관련 에러가 났다. 그래서 이름 바꾸고 다시 냈는데 이번엔 시간 초과가 남. 
그래서 생각해보니까, 어차피 Solve에서 (r, c) 칸에 i를 넣었을 때 맞는지 틀리는지를 판별하는 거니까, 다른 칸 필요 없이 (r, c) 칸만 보면 된다는 걸 
떠올림. 이후 Right가 좌표를 인자로 받아 해당 좌표만 틀렸는지 판단하도록 짰다. 이 과정에서 3*3 정사각형 판별 부분에서 좌표 출발선이 0, 3, 6 
이렇게 올라가야 하는데 곱하기 3을 안 하는 바람에 0, 1, 2 이렇게 올라가게 하는 바람에 좀 고민했었는데, 어쨌든 그거 고치고 제출하니 맞았다.
*/