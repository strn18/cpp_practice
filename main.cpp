#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int E, S, M, ans = 1;

  cin >> E >> S >> M;

  E %= 15; S %= 28; M %= 19;

  while(true){
    if((ans % 15 == E) && (ans % 28 == S) && (ans % 19 == M)) break;
    ans++;
  }

  cout << ans;

  return 0;
}