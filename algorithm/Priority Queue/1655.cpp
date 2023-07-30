#include <iostream>
#include <queue>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, num;
  priority_queue<int> max_pq;
  priority_queue<int, vector<int>, greater<int>> min_pq;

  cin >> N;

  cin >> num;
  max_pq.push(num);
  cout << max_pq.top() << '\n';

  for(int i=1; i<N; i++){
    cin >> num;

    if(max_pq.size() > min_pq.size()){
      if(num <= max_pq.top()){
        max_pq.push(num);
        min_pq.push(max_pq.top());
        max_pq.pop();
      }
      else min_pq.push(num);
    }
    else{
      if(num <= max_pq.top()) max_pq.push(num);
      else{
        min_pq.push(num);
        max_pq.push(min_pq.top());
        min_pq.pop();
      }
    }

    cout << max_pq.top() << '\n';
  }

  return 0;
}

/*
원래는 못 풀고 넘겼었는데, SWEA에서 비슷한 거(No_25) 풀고 다시 풀어 본 문제. 

그 문제 풀이랑 거의 비슷하게, max_pq와 min_pq를 사용하여 풀었다. 자세한 설명은 No_25 풀이 참조
*/