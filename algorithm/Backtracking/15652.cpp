#include <iostream>

using namespace std;

int N, M;
int nums[8];

void solve(int idx, int prev);

int main(){
  scanf("%d %d", &N, &M);
  solve(0, 1);
  return 0;
}

void solve(int idx, int prev){
  for(int i=prev; i<=N; i++){
    nums[idx]=i;
    if(idx==M-1){
      for(int j=0; j<M; j++)
        printf("%d ", nums[j]);
      printf("\n");
    }
    else{
      solve(idx+1, i);
    }
  }
}

/*
15650과 거의 유사한 백트래킹 문제. 중복 선택 가능한 것만 빼면 똑같음
*/