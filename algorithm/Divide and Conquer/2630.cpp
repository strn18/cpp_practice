#include <iostream>
#define MAX 150

using namespace std;

int paper[MAX][MAX];
int count[2] = {0};

void solve(int r, int c, int n);
bool check_color(int r, int c, int n, int color);

int main(){
  int N;

  scanf("%d", &N);
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      scanf("%d", &paper[i][j]);
  
  solve(0, 0, N);

  for(int i=0; i<2; i++)
    printf("%d\n", count[i]);

  return 0;
}

void solve(int r, int c, int n){
  int color = paper[r][c];

  if(check_color(r, c, n, color))
    count[color]++;
  else
    for(int i=r; i<r+n; i+=(n/2))
      for(int j=c; j<c+n; j+=(n/2))
        solve(i, j, n/2);
}

bool check_color(int r, int c, int n, int color){
  for(int i=r; i<r+n; i++)
    for(int j=c; j<c+n; j++)
      if(paper[i][j] != color)
        return false;
  return true;
}

/*
1780이랑 거의 똑같은 분할 정복 문제.
*/