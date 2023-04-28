#include <iostream>
#include <queue>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, K, count = 0;
  queue<int> Q;

  cin >> N >> K;

  for(int i=1; i<=N; i++)
    Q.push(i);

  cout << '<';

  while(!Q.empty()){
    int cur = Q.front();
    Q.pop();

    if(++count == K){
      count = 0;
      
      if(Q.size() != N-1)
        cout << ", ";
      cout << cur;
    }
    else
      Q.push(cur);
  }

  cout << '>';

  return 0;
}