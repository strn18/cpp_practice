#include <iostream>

using namespace std;

long long pow_mod(int a, int b, int mod);

int main(){
  int A, B, C;

  scanf("%d %d %d", &A, &B, &C);

  printf("%d", pow_mod(A, B, C));
  
  return 0;
}

long long pow_mod(int a, int b, int mod){
  if(b == 0) return 1;

  if(b%2 == 0)
    return pow_mod(a, b/2, mod) * pow_mod(a, b/2, mod) % mod;
  else
    return (pow_mod(a, (b-1)/2, mod) * pow_mod(a, (b-1)/2, mod) % mod) * a % mod;
}

/*
어쩌다보니 처음 풀어본 분할정복 문제. 처음에는 단순히 result = 1로 잡고, result에다가 A를 B번 곱하며, 곱한 후엔 매번 C로 나머지 연산을 해주는
단순한 방식으로 풀었다. 그랬더니 시간초과 났음. 당연히, B가 최대 21억 정도니까, A를 B번 곱하는 방식이 시간초과가 안 날리가 없다.

그래서 어떻게 푸는 건지 고민하다가 pow 함수의 시간복잡도가 얼마인지 찾고 있었는데, 우연히 https://mygumi.tistory.com/319 여기 글을 봤다.
사실 그 글에 정답 코드가 나와있기도 했는데, 어쨌든 글 읽으면서 단순히 B번 곱해주는 방식이 아니라, 재귀적으로 풀어야 O(B)가 아니라 O(logB)로
풀 수 있다는 걸 알았다. 그래서 그 방식으로 코드 수정하여 제출했더니 맞았음. pow_mod는, a의 b제곱을 mod로 나머지 연산하여 return 하는 함수이다.
*/