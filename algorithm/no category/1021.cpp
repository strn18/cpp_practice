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

/*
deque을 써서 쉽게 풀 수 있는 문제. 어떠한 수(뽑아내려는 수)가 덱의 왼편이라면 왼쪽의 수들을 pop해서 오른쪽에서 push하면 되고(26행), 오른편이라면
오른쪽의 수들을 pop해서 왼쪽에서 push하면 됨(36행). 그걸 하면서 count값을 증가시켜주면 된다.
*/