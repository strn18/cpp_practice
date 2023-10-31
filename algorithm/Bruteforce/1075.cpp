#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, F;

  cin >> N >> F;

  N -= (N % 100);

  for(int i=0; i<=99; i++){
    if((N + i) % F == 0){
      if(i >= 10) cout << i;
      else cout << 0 << i;
      break;
    }
  }

  return 0;
}