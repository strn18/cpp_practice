#include <iostream>
#include <cstdlib>
#define MAX 1000

using namespace std;

int beat[MAX+1] = {0}, beat_change_sum[MAX+1] = {0};

int main(){
  int N, Q, l, r;

  scanf("%d %d", &N, &Q);

  for(int i=1; i<=N; i++){
    scanf("%d", &beat[i]);
    beat_change_sum[i] = beat_change_sum[i-1]+abs(beat[i]-beat[i-1]);
  }
  
  while(Q--){
    scanf("%d %d", &l, &r);
    printf("%d\n", beat_change_sum[r]-beat_change_sum[l]);
  }

  return 0;
}

/*
쉬운 구간 합 문제.
*/