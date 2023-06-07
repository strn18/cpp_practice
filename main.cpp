#include <iostream>
#include <deque>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int N, M, count = 0;
  deque<int> dq;

  cin >> N >> M;

  for(int i=1; i<=N; i++)
    dq.push_back(i);
  
  for(int i=0; i<M; i++){
    int target, idx;

    cin >> target;
    
    for(idx=0; idx<dq.size(); idx++)
      if(dq[idx] == target) break;
    
    if(idx <= dq.size()/2){
      while(true){
        if(dq.front() == target) break;

        int temp = dq.front();
        dq.pop_front();
        dq.push_back(temp);
        count++;
      }
    }
    else{
      while(true){
        if(dq.front() == target) break;

        int temp = dq.back();
        dq.pop_back();
        dq.push_front(temp);
        count++;
      }
    }

    dq.pop_front();
  }

  cout << count;

  return 0;
}