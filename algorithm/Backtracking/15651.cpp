#include <iostream>

using namespace std;

int N, M;
int nums[7];

void solve(int idx);

int main(){
  scanf("%d %d", &N, &M);
  solve(0);
  return 0;
}

void solve(int idx){
  for(int i=1; i<=N; i++){
    nums[idx] = i;
    if(idx==M-1){
      for(int j=0; j<M; j++)
        printf("%d ", nums[j]);
      printf("\n");
    }
    else{
      solve(idx+1);
    }
  }
}

/*
이것도 쉬운 백트래킹 문제인데 왜 백트래킹인지는 모르겠네 그냥 브루트포스 같은데
*/