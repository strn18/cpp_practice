#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int A, B, C, D;

  cin >> A >> B >> C >> D;

  A += (D / 3600);
  D %= 3600;

  B += (D / 60);
  D %= 60;

  C += D;

  if(C >= 60){
    B++; C -= 60;
  }
  if(B >= 60){
    A++; B -= 60;
  }
  A %= 24;

  cout << A << ' ' << B << ' ' << C;

  return 0;
}