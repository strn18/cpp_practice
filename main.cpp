#include <iostream>
#define MAX 200

using namespace std;

int main(){
  int N, longest = 0;
  int kids[MAX+1], dp[MAX+1];

  scanf("%d", &N);
  for(int i=1; i<=N; i++)
    scanf("%d", &kids[i]);
  
  dp[1] = 1;
  for(int i=2; i<=N; i++){
    int max_dp = 0;
    for(int j=1; j<i; j++)
      if(kids[j] < kids[i] && dp[j] > max_dp)
        max_dp = dp[j];
    dp[i] = max_dp + 1;
  }

  for(int i=1; i<=N; i++)
    longest = max(longest, dp[i]);
  
  printf("%d", N-longest);

  return 0;
}