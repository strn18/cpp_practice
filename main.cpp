#include <iostream>
#define MAX 50

using namespace std;

int N, M, count = 0;
int board[MAX][MAX]; // 0: 빈 칸, 1: 벽, 2: 청소한 칸
int dr[8] = {-1, 0, 1, 0, -1, 0, 1, 0}; // 북, 동, 남, 서
int dc[8] = {0, 1, 0, -1, 0, 1, 0, -1};

void clean(int r, int c, int d);

int main(){
  int first_r, first_c, first_d;

  scanf("%d %d", &N, &M);
  scanf("%d %d %d", &first_r, &first_c, &first_d);
  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      scanf("%d", &board[i][j]);

  clean(first_r, first_c, first_d);

  printf("%d", count);

  return 0;
}

void clean(int r, int c, int d){
  int next_r, next_c, next_d;
  bool flag = false;

  board[r][c] = 2;
  count++;

  while(1){
    for(int i=d+3; i>=d; i--){
      if(0<=r+dr[i] && r+dr[i]<N && 0<=c+dc[i] && c+dc[i]<M && board[r+dr[i]][c+dc[i]] == 0){
        next_r = r+dr[i]; next_c = c+dc[i]; next_d = i%4;
        flag = true;
        break;
      }
    }

    if(flag) break;

    r += dr[d+2]; c += dc[d+2];
    if(r<0 || r>=N || c<0 || c>=M || board[r][c] == 1)
      break;
  }

  if(flag)
    clean(next_r, next_c, next_d);
}