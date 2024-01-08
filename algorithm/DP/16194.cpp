#include <iostream>
#define MAX 1000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  int card[MAX+1], dp[MAX+1];

  cin >> N;

  for(int i=1; i<=N; i++)
    cin >> card[i];
  
  dp[1] = card[1];

  for(int i=2; i<=N; i++){
    int minCost = card[i];

    for(int j=1; j<=i/2; j++)
      minCost = min(minCost, dp[j] + dp[i-j]);
    
    dp[i] = minCost;
  }

  cout << dp[N];

  return 0;
}