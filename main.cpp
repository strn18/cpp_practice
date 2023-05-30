#include <iostream>
#define MAX 100000
#define INF 2100000000

using namespace std;

int num[MAX+1], p_sum[MAX+1] = {0};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int N, K, ans = -INF;

  cin >> N >> K;

  for(int i=1; i<=N; i++){
    cin >> num[i];
    p_sum[i] = p_sum[i-1]+num[i];
  }

  for(int i=K; i<=N; i++)
    ans = max(ans, p_sum[i]-p_sum[i-K]);

  cout << ans;

  return 0;
}