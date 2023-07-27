#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int a, b;

  cin >> a >> b;

  while(a!=0 || b!=0){
    if(a > b) cout << (a%b == 0 ? "multiple" : "neither") << '\n';
    else cout << (b%a == 0 ? "factor" : "neither") << '\n';

    cin >> a >> b;
  }

  return 0;
}