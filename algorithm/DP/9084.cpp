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

/*
약간 변형된 배낭 문제. 처음에는 dp를 2차원 배열로 두고 풀었다(첫번째 제출). dp[i][j]: 1~i번째 동전을 사용할 때 j원을 만드는 경우의 수. 로 했다.
dp[i][j]는 i번째 동전을 0개 사용할 때는 dp[i-1][j]와 같고, 1개 쓸 때는 dp[i-1][j-coin[i]]와 같고, ... 이므로, 그 값들을 모두 더하는 식으로 
풀었다. 근데 https://www.acmicpc.net/source/61524943 여기 풀이대로 dp를 1차원 배열로 두고 풀면 더 효율적인 것 같아서 바꿨음.
dp[i]: i원을 만드는 경우의 수. 이고, 1번째 동전부터 사용해가며 차례대로(총 N번) 갱신한다. 나머지 자세한 설명은
https://yabmoons.tistory.com/556 여기 보면 됨.
*/