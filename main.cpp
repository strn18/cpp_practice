#include <iostream>
#define MAX 1000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, ans = 0;
  int num[MAX], dp[MAX] = {0};

  cin >> N;

  for(int i=0; i<N; i++)
    cin >> num[i];

  for(int i=0; i<N; i++){
    for(int j=i-1; j>=0; j--)
      if(num[j] < num[i]) dp[i] = max(dp[i], dp[j]);
    
    dp[i] += num[i];
  }

  for(int i=0; i<N; i++)
    ans = max(ans, dp[i]);
  
  cout << ans;

  return 0;
}