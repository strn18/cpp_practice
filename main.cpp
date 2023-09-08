#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  while(T--){
    int k, pqSize = 0;
    priority_queue<int> maxPQ;
    priority_queue<int, vector<int>, greater<int>> minPQ;
    unordered_map<int, int> numCount;

    cin >> k;
    
    while(k--){
      string ch;
      int n;

      cin >> ch >> n;

      if(ch == "I"){
        pqSize++;

        maxPQ.push(n);
        minPQ.push(n);
        
        if(numCount.count(n) == 0) numCount[n] = 1;
        else numCount[n]++;
      }
      else{
        if(pqSize == 0) continue;

        pqSize--;
        
        if(n == 1){
          while(numCount[maxPQ.top()] == 0) maxPQ.pop();

          numCount[maxPQ.top()]--;
          maxPQ.pop();
        }
        else{
          while(numCount[minPQ.top()] == 0) minPQ.pop();

          numCount[minPQ.top()]--;
          minPQ.pop();
        }
      }
    }

    if(pqSize == 0) cout << "EMPTY" << '\n';
    else{
      while(numCount[maxPQ.top()] == 0) maxPQ.pop();
      while(numCount[minPQ.top()] == 0) minPQ.pop();

      cout << maxPQ.top() << ' ' << minPQ.top() << '\n';
    }
  }

  return 0;
}