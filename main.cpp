#include <iostream>
#define MAX 1000000

using namespace std;

int p_xor[MAX+1] = {0};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, Q, ans = 0;
  int num, s, e;

  cin >> N >> Q;

  for(int i=1; i<=N; i++){
    cin >> num;
    p_xor[i] = (p_xor[i-1]^num);
  }
  
  while(Q--){
    cin >> s >> e;
    ans ^= (p_xor[e]^p_xor[s-1]);
  }

  cout << ans;

  return 0;
}