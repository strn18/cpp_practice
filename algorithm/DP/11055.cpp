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

/*
11053이랑 거의 비슷한 dp문제. 11053은 가장 '긴' 증가하는 부분 수열이라, 수의 개수가 최대가 되도록 하는 거였고 이거는 가장 '큰' 증가하는
부분 수열이라, 수의 합이 최대가 되도록 하는 거임. 근데 풀이 방법은 거의 비슷하다. dp[i]: i번째 수를 고를 때(증가하는 부분 수열의 마지막
수로 포함시킬 때), 그 수열의 수의 합의 최댓값. 이다. 즉 예제로 주어진 1 100 2 50 60 3 5 6 7 8 에서, dp[0] = 1, dp[1] = 101,
dp[2] = 3, ... 이런 식임. 그럼 점화식은 어떻게 되느냐? j가 i-1부터 0까지 돌면서, num[j]<num[i]라면? j번째 수를 마지막 수로 포함시킨 그
수열의 뒤에 i번째 수를 넣을 수 있으니깐, 우선 dp[i]를 최댓값 갱신시킴(20행). 그런 다음 다 끝나면, 뒤에 i번째 수를 넣으면 되니깐 22행에서
num[i]를 더해준다. 이렇게 한 다음, max(dp)를 출력하면 된다.
*/