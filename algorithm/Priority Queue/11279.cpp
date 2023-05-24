#include <iostream>
#include <queue>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, x;
  priority_queue<int> pq;

  cin >> N;

  while(N--){
    cin >> x;

    if(x==0){
      if(pq.empty()) cout << 0;
      else{
        cout << pq.top();
        pq.pop();
      }

      cout << '\n';
    }
    
    else pq.push(x);
  } 

  return 0;
}

/*
그냥 기초 pq 문제.
*/