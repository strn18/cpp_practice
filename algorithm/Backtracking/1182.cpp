#include <iostream>

using namespace std;

int N, S, count = 0;
int num[20];

void solve(int sum, int n); // 지금까지 합은 sum, n번째 수를 고르기

int main(){
  scanf("%d %d", &N, &S);
  for(int i=0; i<N; i++)
    scanf("%d", &num[i]);

  solve(0, 0);

  printf("%d", count);
  
  return 0;
}

void solve(int sum, int n){
  sum += num[n];
  if(sum == S)
    count++;

  if(n == N-1) return;

  solve(sum, n+1);
  sum -= num[n];
  solve(sum, n+1);
}

/*
옛날에 무지성 for문으로 풀었던 문제를 다시 백트래킹으로 제대로 풀어보았음. 어려운 문제는 아니고, 그냥 어떠한 인덱스의 수를 골랐을 때와 안 골랐을
때로 나누어서, 그 다음 수로 넘어가주면 된다. 그렇게 하여 약 2^20 = 100만 정도의 연산으로 풀 수 있음.
*/