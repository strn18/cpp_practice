// 사탕 분배(10. 분할정복)
#include <iostream>

using namespace std;

int mod;

long long pow_mod(int n); // return 2^n % mod

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    int A, B, K;
    long long ans;

    cin >> A >> B >> K;

    mod = A+B;

    ans = (A * pow_mod(K)) % mod;

    cout << '#' << t << ' ' << min(ans, mod-ans) << '\n';
  }

  return 0;
}

long long pow_mod(int n){
  if(n == 1) return 2 % mod;

  long long half, total = 1;

  if(n%2 == 0){
    half = pow_mod(n/2);

    total = (total*half) % mod;
    total = (total*half) % mod;
  }
  else{
    half = pow_mod((n-1)/2);
    
    total = (total*half) % mod;
    total = (total*half) % mod;
    total = (total*pow_mod(1)) % mod;
  }

  return total;
}

/*
쫌 어려웠던 문제... 단순히 주어진 연산을 K번 하게 되면 백프로 시간초과가 난다.

처음에는 주기를 찾으면 그 즉시 연산을 종료하고 답을 찾는 방식으로 했다. unordered_map을 사용하여, 연산 결과로 나오는 (A', B')를 map에 
저장해두고(문자열 형태), 만약 map에 이미 그게 있다면 주기를 찾은 거니까 나머지 연산을 잘 쳐서 바로 답을 찾도록 했다. 
일단 나머지 연산 부분이 좀 미완성이었는데 시간초과되는지 테스트해보려고 제출해봤다. 그랬더니 시간초과남.

그래서 고민하다가 https://velog.io/@dndud1024/SWEA-13736-D4-C-%EC%82%AC%ED%83%95%EB%B6%84%EB%B0%B0 여기를 참고했다.
이 풀이의 핵심은 다음과 같다. 
원래는 A, B가 연산을 한 번 거치게 되면 A, B -> 2A, B-A 가 되는데, 이는 A <= B 인 경우에만 성립하게 된다. 그렇기 때문에, 연산을 몇 번 거쳐서 
A가 B보다 커지게 되면 위의 연산을 사용하지 못하고, 다시 반대로 바꿔야 한다. 즉, 위의 연산을 몇 번 해야 A > B 가 되는지를 알아야 한다는 것이고, 
그렇기에 매 연산을 계속 해봐야 한다는 문제가 있다.
링크의 풀이는 이를 극복하기 위해, A와 B에 가해지는 연산이 똑같은 형태가 되도록 연산을 변형하였다. 우선 결과부터 말하자면 
A, B -> 2A%(A+B), 2B%(A+B) 이다. 왜 이렇게 되느냐? 우선 A <= B 인지 아닌지 모른다고 가정하자. 이때, 두 수에 모두 2를 곱한다면? 만약 A > B 라면 
2A, 2B에서 2B는 정상적인 연산 결과이다. 하지만 2A는 그렇지 않고, 두 수의 합이 계속 A+B로 보존되어야 하는데 2A+2B가 되어 A+B만큼 오버되었다. 애초에 
2를 곱했으니 A+B만큼 오버되는 건 당연함. 그러므로, 오버된 2A에 대해서, A+B로 나머지 연산을 해줌으로써, 오버된 A+B만큼이 다시 감소되도록 만든다. 
즉, 2A가 아니라 2A%(A+B)가 되도록 하는 것이다. 이때, A와 B에 가해지는 연산이 같아야 하는데, 2B%(A+B)를 해도 문제가 없다(2B와 값이 같음). 왜냐? 
애초에 A > B(또는 A >= B. 등호 상관 x)였으니까, B를 2배 해봤자 A+B보다 커지지 않고, A+B로 나머지 연산을 해도 값은 보존된다.

그렇기에, 이제 A와 B에 대해서 둘 다 동일한 연산을 취할 수 있게 된다. 값을 두 배로 만든 후 A+B로 나머지 연산을 하면 되는 것이다.

그러므로 이제 걱정없이 A(또는 B)에 대해서 위의 연산을 K번 해주고 그 값을 ans에 저장한다. 그런 다음, min(ans, A+B - ans)를 출력하면 된다.

A -> 2A % (A+B) 연산을 K번 해주는 건 어떻게 구현할까? 어차피 mod 연산은 중간중간에 오버플로우 안 나도록 계속 해주고, 마지막에 해주고 리턴하기만 
하면 됨. 그러므로 그냥 2를 곱해주는 걸 K번 해주는 거랑 거의 비슷함. 즉, A에 2^K를 곱하고, 거기에 A+B로 mod 연산 쳐주면 되는 것임. 

이를 위해 pow_mod 함수를 만들었다. 얘는 2^n을 리턴하는데, 이때 오버플로우가 나지 않도록 A+B로 mod 연산을 중간중간 계속 해준다. 분할정복 방식으로 
짰음. 
*/