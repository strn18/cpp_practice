#include <iostream>
#define MAX 15

using namespace std;

int N, ans = 0;
int T[MAX+1], P[MAX+1];

void choose(int n, int sum);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N;

  for(int i=1; i<=N; i++)
    cin >> T[i] >> P[i];

  choose(1, 0);

  cout << ans;

  return 0;
}

void choose(int n, int sum){
  if(n > N){
    ans = max(ans, sum);
    return;
  }

  if(n+T[n]-1 <= N) choose(n+T[n], sum+P[n]);
  if(T[n] != 1) choose(n+1, sum);
}

/*
브루트포스로 풀리는 문제. N이 최대 15라서 모든 경우를 다 찾아봐도 2^15 정도면 다 찾을 수 있다. 
dp로도 풀 수 있음. i번째 날에 상담하거나 하지 않았을 때를 가지고 dp 테이블을 채워주면 될듯.
*/