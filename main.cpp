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