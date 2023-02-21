#include <iostream>
#define MAX 2200

using namespace std;

int paper[MAX][MAX];
int count[3] = {0};

void solve(int n, int r, int c); // n*n 크기, (r, c)에서 시작하는 종이

int main(){
  int N;

  scanf("%d", &N);
  for(int i=1; i<=N; i++)
    for(int j=1; j<=N; j++)
      scanf("%d", &paper[i][j]);

  solve(N, 1, 1);

  for(int i=0; i<3; i++)
    printf("%d\n", count[i]);

  return 0;
}

void solve(int n, int r, int c){
  bool flag = true;
  int num = paper[r][c];
  
  for(int i=r; i<r+n; i++){
    for(int j=c; j<c+n; j++){
      if(paper[i][j] != num){
        flag = false;
        break;
      }
    }
    if(!flag) break;
  }

  if(!flag)
    for(int i=r; i<r+n; i+=(n/3))
      for(int j=c; j<c+n; j+=(n/3))
        solve(n/3, i, j);
  else
    count[num+1]++;
}