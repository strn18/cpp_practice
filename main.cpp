#include <iostream>
#include <cmath>

using namespace std;

int N, N_digit, count;
bool broken[10] = {false};

int get_digit(int n);
void solve(int cur, int cur_digit);

int main(){
  int M, temp;

  scanf("%d", &N);
  scanf("%d", &M);
  for(int i=0; i<M; i++){
    scanf("%d", &temp);
    broken[temp] = true;
  }

  N_digit = get_digit(N);
  count = abs(N-100); // 처음 채널에서 +, -로만 이동
  if(!broken[0])
    count = min(count, N+1); // 0으로 간 후 +, -로만 이동

  for(int i=1; i<=9 && count!=0; i++)
    if(!broken[i])
      solve(i, 1);

  printf("%d", count);

  return 0;
}

int get_digit(int n){
  for(int i=1; 1; i++)
    if(n<pow(10, i))
      return i;
}

void solve(int cur, int cur_digit){
  count = min(count, abs(N-cur)+cur_digit);

  if(cur_digit == N_digit+1) return;

  for(int i=0; i<=9; i++)
    if(!broken[i])
      solve(cur*10+i, cur_digit+1);
}