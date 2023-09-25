#include <iostream>

using namespace std;

int GCD(int a, int b);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int a1, b1, a2, b2;

  cin >> a1 >> b1 >> a2 >> b2;

  int A = a1*b2 + a2*b1;
  int B = b1 * b2;

  int gcd = GCD(max(A, B), min(A, B));

  cout << (A / gcd) << ' ' << (B / gcd);

  return 0;
}

int GCD(int a, int b){
  while(true){
    if(a % b == 0) return b;

    int temp = a % b;
    a = b;
    b = temp;
  }
}

/*
그냥 두 분수를 통분해서 더하고( a/b + c/d = (ad + cb)/bd 이용하기), 분자와 분모의 최대공약수(gcd)를 구한 다음 그걸로 분자와 분모를 나눠주면 된다.

처음에 GCD 함수는 그냥 단순히 구현했다. 2부터 모든 수를 돌면서, 그 수로 a와 b를 나눴을 때 나머지가 0이 아닐 때까지 계속 나눠준다. 다 나눴으면 
다음 수로 넘어간다. 좀 원시적인 방법임(첫번째 제출).

근데 시간이 너무 오래 걸려서, 찾아보니 유클리드 알고리즘이 있었다. https://blockdmask.tistory.com/53 사실 예전에 찾아봤던 것 같은데 기억이 안 났음.
그래서 수정해서 제출하니 더 빠른 시간으로 맞았다. 
*/