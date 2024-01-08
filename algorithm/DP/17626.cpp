#include <iostream>
#include <algorithm>
#define MAX 50000
#define SQR 223

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, dp[MAX+1];

  cin >> N;

  fill_n(dp+1, MAX, MAX);

  for(int i=1; i<=SQR; i++)
    dp[i*i] = 1;
  
  for(int i=1; i<=N; i++){
    if(dp[i] == 1) continue;

    for(int j=1; j*j<=i; j++){
      dp[i] = min(dp[i], dp[i - j*j] + 1);
    }
  }

  cout << dp[N];

  return 0;
}

/*
접근 1) dp[i] = min(dp[1] + dp[i-1], dp[2] + dp[i-2], ...) 로 했었는데, 그러면 O(N^2)이라 시간초과 남. 
접근 2) 어차피 모든 수는 4개 이하로 표현 가능하댔으니까, 1*1, 2*2, ..., 223*223 중에서 중복 포함 1개를 뽑아 만든 수들은 1개로 표현 가능한 거고, 
2개를 뽑아서 더해서 나온 수는 2개로 표현 가능한 거고, 3개를 뽑아서 더해서 나온 수는 3개로 표현 가능한 거니까 그냥 1중for문 2중for문 3중for문으로 
다 구함. 다른 수들은 4개로 표현 가능한 것이다. 이렇게 하니까 맞긴 했음. 
접근 3) 접근 1에는 문제가 있었는데, 너무 비효율적이었음. https://ip99202.github.io/posts/%EB%B0%B1%EC%A4%80-17626-Four-Squares/ 여기 
설명처럼, dp[i] = min(dp[i - 1] + 1, dp[i - 4] + 1, dp[i - 9] + 1, ...) 이것만 보면 됨. 어차피 반드시 그 중 하나에 답이 있으니까. 
*/