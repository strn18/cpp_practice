#include <iostream>
#define MAX 100000

using namespace std;

int dp[MAX+1] = {0};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  cin >> N;

  for(int i=1; i<=N; i++){
    int minimum = i;

    for(int j=1; j*j<=i; j++)
      minimum = min(minimum, 1+dp[i-(j*j)]);

    dp[i] = minimum;
  }

  cout << dp[N];

  return 0;
}