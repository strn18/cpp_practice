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

/*
쉬운 부분합 문제. 근데 꼭 부분합으로 안 풀어도 될듯. 그냥 1일~K일부터 시작해서, 맨 앞 날짜의 온도를 빼고 맨 뒤의 다음 날의 온도를 더하고 이런
식으로 쭉 해나가도 될듯. 1일~K일, 2일~K+1일, ... 이렇게
*/