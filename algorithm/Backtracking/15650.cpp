#include <iostream>

using namespace std;

int N, M;
int nums[8];

void solve(int prev, int count);

int main(){
  scanf("%d %d", &N, &M);
  solve(0, 0);
  
  return 0;
}

void solve(int prev, int count){
  for(int i=prev+1; i<=N; i++){
    nums[count]=i;
    if((count+1)==M){
      for(int j=0; j<M; j++)
        printf("%d ", nums[j]);
      printf("\n");
    }
    else
      solve(i, count+1);
  }
}

/*
쉬운 백트래킹 문제. 원래 dfs로 제대로 푼다면 visited를 추가하여 방문한 숫자는 다시 방문하지 않는 식으로 짰겠지만 
어차피 1~N 오름차순 수를 사용하는 것이기에 그냥 prev 인자를 넣어서 사용한 수 이후의 수부터 for문이 시작하는 식으로 했음.
*/