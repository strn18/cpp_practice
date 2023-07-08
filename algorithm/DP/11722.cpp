#include <iostream>
#define MAX 1000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, ans = 0;
  int num[MAX], dp[MAX];

  cin >> N;

  for(int i=0; i<N; i++){
    cin >> num[i];

    int max_dp = 0;

    for(int j=0; j<i; j++)
      if(num[j] > num[i]) max_dp = max(max_dp, dp[j]);

    dp[i] = max_dp + 1;
    ans = max(ans, dp[i]);
  }

  cout << ans;

  return 0;
}

/*
11053이랑 거의 똑같은 dp 문제.
*/