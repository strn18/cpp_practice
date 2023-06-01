#include <iostream>
#define MAX_COIN 20
#define MAX_VAL 10000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  while(T--){
    int N, M;
    int coin[MAX_COIN+1];
    int dp[MAX_VAL+1] = {1};

    cin >> N;

    for(int i=1; i<=N; i++)
      cin >> coin[i];
    
    cin >> M;

    for(int i=1; i<=N; i++)
      for(int j=coin[i]; j<=M; j++)
        dp[j] += dp[j-coin[i]];

    cout << dp[M] << '\n';
  }

  return 0;
}