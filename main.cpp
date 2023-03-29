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