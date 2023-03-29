#include <iostream>
#define MAX 2000

using namespace std;

int num[MAX+1];
int dp[MAX+1][MAX+1];

int is_palin(int i, int j);

int main(){
  int N, M, S, E;

  fill_n(dp[0], (MAX+1)*(MAX+1), -1);

  scanf("%d", &N);
  for(int i=1; i<=N; i++)
    scanf("%d", &num[i]);

  scanf("%d", &M);
  while(M--){
    scanf("%d %d", &S, &E);

    printf("%d\n", is_palin(S, E));
  }
  
  return 0;
}

int is_palin(int i, int j){
  if(dp[i][j] != -1) return dp[i][j];

  if(j-i+1 <= 3) return dp[i][j] = (num[i] == num[j] ? 1 : 0);

  if(num[i] == num[j] && is_palin(i+1, j-1)) return dp[i][j] = 1;
  else return dp[i][j] = 0;  
}

/*
어렵지 않았던 dp문제. 어떻게 dp테이블을 구성할지 좀 고민하다가, [i, j]가 회문인지 확인하려면? 우선 num[i] == num[j]이어야 하고, [i+1, j-1]이
회문이어야 한다는 걸 캐치함. 그래서 i부터 j 구간이 회문인지 확인하는 함수인 is_palin을 정의했다. 기저 조건으로는, i부터 j까지의 길이(수의 개수)가
3 이하라면? num[i] == num[j] 이것만 체크해주면 된다. 어차피 i와 j 사이의 수는 없거나 딱 한 개일 테니까 체크할 필요 없다.
*/