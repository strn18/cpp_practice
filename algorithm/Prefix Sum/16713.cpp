#include <iostream>
#define MAX 1000000

using namespace std;

int p_xor[MAX+1] = {0};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, Q, ans = 0;
  int num, s, e;

  cin >> N >> Q;

  for(int i=1; i<=N; i++){
    cin >> num;
    p_xor[i] = (p_xor[i-1]^num);
  }
  
  while(Q--){
    cin >> s >> e;
    ans ^= (p_xor[e]^p_xor[s-1]);
  }

  cout << ans;

  return 0;
}

/*
xor의 특징만 찾으면 쉬웠던 문제. 쿼리로 (s, e)를 받으면, num[s]부터 num[e]를 xor한다. 쿼리마다의 이 각각의 값들을 모두 xor한 것이 최종 답이 된다.
p_xor[i]에는, num[1]부터 num[i]까지 xor한 값을 넣어둔다. 이때, num[s]부터 num[e]를 xor한 값을 알고 싶다면? p_xor[e]^p_xor[s-1]을 해주면 된다.
왜냐? num[1]^num[2]^...^num[x] = X라고 했을 때, num[i]^num[i+1]^...^num[x] = X^(num[1]^num[2]^...^num[i-1])과 같기 때문이다(직접 계산해서 규칙
알아냈음). 이걸 알고 쿼리마다의 값을 ans에 계속 xor해주고, 마지막에 ans를 출력해주면 된다.
*/