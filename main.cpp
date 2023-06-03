#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, five = 5, ans = 0;

  cin >> N;

  while(five <= N){
    ans += N/five;

    five *= 5;
  }

  cout << ans;

  return 0;
}