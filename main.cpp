#include <iostream>
#include <queue>
#include <cstdlib>

using namespace std;

struct compare{
  bool operator()(int a, int b){
    if(abs(a) != abs(b))
      return abs(a) > abs(b);
    else
      return a > b;
  }
};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  priority_queue<int, vector<int>, compare> pq;

  cin >> N;

  while(N--){
    int x;

    cin >> x;

    if(x==0){
      if(pq.empty()) cout << 0;
      else{
        cout << pq.top();
        pq.pop();
      }
      cout << '\n';
    }
    else
      pq.push(x);
  }

  return 0;
}