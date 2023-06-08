#include <iostream>

using namespace std;

int GCD(int a, int b); // a, b의 최대공약수 return

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  while(T--){
    int A, B;

    cin >> A >> B;

    cout << (A*B)/GCD(A, B) << '\n';
  }

  return 0;
}

int GCD(int a, int b){
  if(a % b == 0) return b;

  return GCD(b, a%b);
}

/*
걍 최소공배수 구하는 문제. 첨에는 소인수분해 하나한 하는 느낌으로 풀었는데, 2609에서 썼던 방법대로, (A*B)/(A와 B의 최대공약수) 를 하면 
최소공배수를 구할 수 있음.
*/