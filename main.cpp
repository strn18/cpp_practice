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