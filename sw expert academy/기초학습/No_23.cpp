// 힙(7. Heap)
#include <iostream>
#include <queue>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    int N;
    priority_queue<int> pq;

    cin >> N;
    
    cout << '#' << t << ' ';

    while(N--){
      int num;

      cin >> num;

      if(num == 1){
        int x;
        cin >> x;
        pq.push(x);
      }
      else{
        cout << (pq.empty() ? -1 : pq.top()) << ' ';
        
        if(!pq.empty()) pq.pop();
      }
    }

    cout << '\n';
  }

  return 0;
}