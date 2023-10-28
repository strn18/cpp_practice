#include <iostream>
#define ll long long

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;

  while(cin >> n){
    ll target = 1;
    int digits = 1;

    while(target % n){
      target *= 10;
      target++;
      digits++;

      target %= n;
    }

    cout << digits << '\n';
  }

  return 0;
}