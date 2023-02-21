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

/*
쉬웠던 분할정복 문제. n*n의 종이(n은 3의 제곱꼴)가 있을 때, 만약 모든 칸의 숫자가 같다면 그 숫자의 개수(count 배열)를 하나 증가시키고, 그렇지
않다면 가로 3 세로 3 총 9개로 나눠서, 각각의 부분에 대해 위의 검사를 다시 실시하면 된다.

solve는 (r, c)에서 시작하는(해당 칸이 좌상칸) n*n 크기의 종이에 대해 위의 작업을 실시하는 함수이다. 우선 모든 칸을 돌면서, 숫자가 다 같은지 
검사하고, 다르다면(flag is false) 9분할해서 solve 함수를 다시 재귀를 친다. 만약 숫자가 다 같다면 해당 숫자의 count값(숫자는 -1, 0, 1이므로,
숫자+1에 해당하는 인덱스 값)을 하나 늘리면 된다.
*/