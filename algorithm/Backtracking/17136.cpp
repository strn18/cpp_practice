#include <iostream>
#define MAX 10
using namespace std;

int board[MAX][MAX];
int paper[6] = {0, 5, 5, 5, 5, 5};
int minimum = 99;

void solve(int r, int c); // (r, c)가 1이면 put_n(n = 1~5) 호출. 거기서 1 리턴되면 solve(다음 칸) 한 후 detach()로 지워줌.
// (r, c)가 1이 아니면 그냥 solve(다음 칸)
int put_n(int r, int c, int n); // (r, c)에 n*n 색종이를 놓을 수 있으면 놓고 1 리턴, 놓을 수 없으면 0 리턴
void detach(int r, int c, int n); // (r, c)에 있는 n*n 색종이를 지움
void update_min(void); // 색종이 최소 개수 갱신

int main(){
  for(int i=0; i<MAX; i++)
    for(int j=0; j<MAX; j++)
      scanf("%d", &board[i][j]);

  solve(0, 0);

  if(minimum == 99)
    minimum = -1;
  printf("%d", minimum);

  return 0;
}

void solve(int r, int c){
  int next_r = r, next_c = c+1;
  if(r==10){
    update_min();
    return;
  }
  if(next_c == 10){
    next_c = 0; next_r++;
  }
  
  if(board[r][c]==1){
    for(int i=1; i<=5; i++){
      if(put_n(r, c, i)){
        solve(next_r, next_c);
        detach(r, c, i);
      }
    }
  }
  else{
    solve(next_r, next_c);
  }
}

int put_n(int r, int c, int n){
  if(!paper[n]) return 0; // 색종이가 없을 경우

  if(r>MAX-n || c>MAX-n) return 0; // 색종이 붙일 칸이 범위 밖일 경우

  for(int i=r; i<r+n; i++)
    for(int j=c; j<c+n; j++)
      if(board[i][j] != 1) // 색종이 붙일 칸이 1이 아닐 경우
        return 0;

  for(int i=r; i<r+n; i++)
    for(int j=c; j<c+n; j++)
      board[i][j] = 2;
  paper[n]--;
  return 1;
}

void detach(int r, int c, int n){
  for(int i=r; i<r+n; i++)
    for(int j=c; j<c+n; j++)
      board[i][j] = 1;
  paper[n]++;
}

void update_min(void){
  int total = 25;
  for(int i=1; i<=5; i++)
    total -= paper[i];
  minimum = min(total, minimum);
}

/*
크게 어렵진 않았던 백트래킹 문제. 모든 칸을 탐색하며 1을 발견했을 때 해당 칸에 1*1부터 5*5크기의 색종이를 다 붙여보고, 붙일 수 있으면 다음 칸으로
넘어가는 방식으로 풀면 어렵지 않게 풀 수 있다. 이때 해당 칸에 그 색종이를 붙였을 때의 모든 경우 탐색이 끝난 후 색종이를 다시 떼주는 과정을
까먹었었는데, detach 함수 추가하니 답이 제대로 나왔다. 여기서 더 최적화를 하자면, 지금은 put_n 함수에서 색종이가 없을 때, 붙일 칸이 범위 밖일 때,
붙일 칸이 1이 아닐 때 모두 0을 리턴한다. 이걸 색종이가 없을 때만 0을 리턴하고 다른 두 경우일 때 -1을 리턴하게 한 다음, 41행에서 put_n의 리턴이 
-1이면 다음 for문을 더 도는게 아니라 그냥 바로 리턴하는 식으로 하면 시간이 조금 더 줄어들 것 같다. 왜냐면 현재 색종이를 붙일 칸이 범위 밖이거나 
1이 아니라면, 다음 색종이(크기가 더 큰) 역시 절대 붙일 수 없기 때문에 굳이 더 for문을 돌 필요가 없을듯.
바꿔서 제출하니깐(이거는 원래 코드고 바꾼 코드는 백준에 있음) 시간이 좀 줄어들긴 했다 많이는 아니고..
*/