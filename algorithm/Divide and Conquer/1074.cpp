#include <iostream>
#include <cmath>
#define MAX 40000

using namespace std;

int Count(int n, int row, int col);

int main(){
  int N, r, c;

  scanf("%d %d %d", &N, &r, &c);

  printf("%d", Count(N, r, c));

  return 0;
}

int Count(int n, int row, int col){
  if(n==0) return 0;

  int half = pow(2, n-1);

  if(row < half){
    if(col < half)
      return Count(n-1, row, col);

    else
      return (half*half) + Count(n-1, row, col-half);
  }
  else{
    if(col < half)
      return (half*half*2) + Count(n-1, row-half, col);

    else
      return (half*half*3) + Count(n-1, row-half, col-half);
  }
}

/*
1780, 1992와 유사한 분할정복 문제. 그 문제들과 마찬가지로, 주어진 영역을 분할해서 푸는 방식이다.
이 문제에서는 주어진 2^n * 2^n 영역을 4개의 2^(n-1) * 2^(n-1) 영역으로 나누고, (row, col)이 4개 중 어느 영역에 위치하는지 알아낸 후,
해당 영역에 n과 row, col을 조정해서 다시 Count 함수를 쳐주면 된다. 이때, 지금까지 지나온 칸(더 먼저 방문하는 칸)의 개수를 더해주어야 한다.
*/