#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, five = 5, ans = 0;

  cin >> N;

  while(five <= N){
    ans += N/five;

    five *= 5;
  }

  cout << ans;

  return 0;
}

/*
2004랑 쫌 비슷한 문제. 근데 이거는 N! 이라서, 1 * 2 * ... * N 이기 때문에 2의 개수는 반드시 5의 개수보다는 많음. 그래서 5의 개수(정확히 말하자면
5가 몇 번 곱해졌는지)만 구하면 된다. 그러므로, N//5 + N//25 + N//125 + ... 를 해주면 끝.
*/