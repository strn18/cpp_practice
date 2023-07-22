#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int a, b, c;

  cin >> a >> b >> c;

  if(a < b){
    if(a < c) cout << a << ' ' << (b < c ? b : c) << ' ' << (b < c ? c : b);
    else cout << c << ' ' << a << ' ' << b;
  }
  else{
    if(b < c) cout << b << ' ' << (a < c ? a : c) << ' ' << (a < c ? c : a);
    else cout << c << ' ' << b << ' ' << a;
  }

  return 0;
}