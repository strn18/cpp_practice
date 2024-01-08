#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int A, B, C, D, E, total = 0;

  cin >> A >> B >> C >> D >> E;

  if(A < 0){
    total += (-A) * C;
    total += D;
    A = 0;
  }

  total += (B - A) * E;

  cout << total;

  return 0;
}