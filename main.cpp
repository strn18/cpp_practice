#include <iostream>
#define MAX 20

using namespace std;

typedef struct{int r, c;} pos;

int board[MAX][MAX];

int cut(pos start, pos end, int dir);
int count_func(pos start, pos end, int which);

int main(){
  int N, ans;

  scanf("%d", &N);
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      scanf("%d", &board[i][j]);

  ans = cut({0, 0}, {N-1, N-1}, 0) + cut({0, 0}, {N-1, N-1}, 1);

  printf("%d", ans==0 ? -1 : ans);

  return 0;
}

int cut(pos start, pos end, int dir){
  int imp = count_func(start, end, 1);
  int jewel = count_func(start, end, 2);

  if(imp == 0){
    if(jewel == 1) return 1;
    else return 0;
  }
  if(jewel <= 1) return 0;

  int count = 0;
  
  if(dir == 0){
    for(int cut_r = start.r+1; cut_r <= end.r-1; cut_r++){
      if(count_func({cut_r, start.c}, {cut_r, end.c}, 1) && !count_func({cut_r, start.c}, {cut_r, end.c}, 2)){
        count += (cut(start, {cut_r-1, end.c}, 1) * cut({cut_r+1, start.c}, end, 1));
      }
    }
  }

  else{
    for(int cut_c = start.c+1; cut_c <= end.c-1; cut_c++){
      if(count_func({start.r, cut_c}, {end.r, cut_c}, 1) && !count_func({start.r, cut_c}, {end.r, cut_c}, 2)){
        count += (cut(start, {end.r, cut_c-1}, 0) * cut({start.r, cut_c+1}, end, 0));
      }
    }
  }

  return count;
}

int count_func(pos start, pos end, int which){
  int count = 0;

  for(int i=start.r; i<=end.r; i++)
    for(int j=start.c; j<=end.c; j++)
      if(board[i][j]==which)
        count++;

  return count;
}