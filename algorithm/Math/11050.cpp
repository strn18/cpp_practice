#include <iostream>

using namespace std;

int factorial(int n);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, K;

  cin >> N >> K;

  cout << factorial(N)/(factorial(N-K)*factorial(K));

  return 0;
}

int factorial(int n){
  if(n<=1) return 1;

  return n*factorial(n-1);
}

/*
N의 최댓값이 10밖에 안 될 때 NCK를 구하는 문제. 범위가 작으니 dp를 쓸 필요 없이 걍 factorial 재귀함수를 쓰면 된다.
*/