#include <iostream>
#include <unordered_set>
#define MAX 100000

using namespace std;

int train[MAX+1] = {0};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, ans = 0;
  unordered_set<int> s;

  cin >> N >> M;

  while(M--){
    int op, i, x;

    cin >> op;

    switch(op){
    case 1:
      cin >> i >> x;
      train[i] |= (1 << (x-1));
      break;

    case 2:
      cin >> i >> x;
      train[i] &= ~(1 << (x-1));
      break;

    case 3:
      cin >> i;
      train[i] = train[i] << 1;
      train[i] &= ~(1 << 20);
      break;
    
    default:
      cin >> i;
      train[i] = train[i] >> 1;
      break;
    }
  }

  for(int i=1; i<=N; i++){
    if(s.count(train[i]) == 0){
      s.insert(train[i]);
      ans++;
    }
  }

  cout << ans;

  return 0;
}