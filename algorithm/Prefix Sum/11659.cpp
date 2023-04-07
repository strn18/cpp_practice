#include <iostream>
#define MAX 100000

using namespace std;

int num[MAX+1], sum[MAX+1] = {0};

int main(){
  int N, M, l, r;

  scanf("%d %d", &N, &M);

  for(int i=1; i<=N; i++){
    scanf("%d", &num[i]);
    sum[i] += (sum[i-1]+num[i]);
  }
  
  while(M--){
    scanf("%d %d", &l, &r);
    printf("%d\n", sum[r]-sum[l-1]);
  }

  return 0;
}

/*
쉬운 구간 합 문제.
*/