#include <iostream>

using namespace std;

void star(int n, int r, int c){
  if(n==1)
    printf("*");
  else if(r/(n/3) == 1 && c/(n/3) == 1)
    printf(" ");
  else
    star(n/3, r%(n/3), c%(n/3));
}

int main(){
  int N;

  scanf("%d", &N);

  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++)
      star(N, i, j);
    printf("\n");
  }

  return 0;
}

/*
예전에 C랑 파이썬으로 풀었던 문제. C로 풀었던 풀이랑 비슷한 방식으로 풀었는데, 좀 더 (내 기준으로) 깔끔하게 푼 것 같다.

모든 칸에 대해 star 함수를 실행하는 방식으로, 만약 이번에 실행된 star 함수의 n 인자가 1이라면, 기저 조건에 도달했으므로 별을 출력한다.
그렇지 않고, 만약 r과 c를 (n/3)으로 나눈 값이 모두 1이라면, 즉 9분할을 했을 때 중앙에 위치한다면, 빈 칸을 출력한다. 그렇지 않다면,
n은 3으로 나누고, r과 c는 (n/3)으로 나눈 나머지를 인자로 star 함수를 다시 실행한다. 즉, 9분할을 했을 때 중앙을 제외한 나머지 8칸에
위치할 때, r과 c가 9분할을 한 그 작아진 칸을 대상으로하는 좌표값이 되도록(작아진 칸의 좌상칸을 (0, 0)으로 하는 좌표값이 되도록) r과 c를
바꿔서 star를 실행하는 느낌이다. 
*/