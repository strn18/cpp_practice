#include <iostream>

using namespace std;

int bit_count(int bit); // bit에서 1비트 개수 구하기
int bit_delete(int bit, int n); // bit에서 1비트 n개 없애기(왼쪽부터)

int main(){
  int N, K, buy = 0;

  scanf("%d %d", &N, &K);

  if(bit_count(N) > K){
    N = bit_delete(N, K-1);

    for(int i=0; 1; i++){
      if((1<<i) >= N){
        buy = (1<<i) - N;
        break;
      }
    }
  }
  
  printf("%d", buy);

  return 0;
}

int bit_count(int bit){
  if(bit==0) return 0;
  return bit%2 + bit_count(bit/2);
}

int bit_delete(int bit, int n){
  int count = 0;

  for(int i=25; count<n; i--){
    if(bit & (1<<i)){
      bit &= ~(1<<i);
      count++;
    }
  }

  return bit;
}