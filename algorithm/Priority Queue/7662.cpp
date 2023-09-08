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

/*
꽤 까다로웠던 문제. 최대 힙과 최소 힙 두 개를 사용하는 pq 문제는 풀어본 적이 있는데, 이 문제도 그렇게 푸는 것 같아 생각해봤는데, 
풀이 방법이 잘 떠오르지 않았음. 1655번 문제를 풀 때는 큰 값들을 최소 힙, 그보다 작은 값들을 최대 힙에 넣고, 둘의 사이즈가 같거나 
한쪽이 1만큼만 크도록 계속 유지하면서(1보다 더 커지려 할 때는 한쪽의 최솟값/최댓값을 다른 쪽에 넣으면서) 중간값을 구하는 방식이었다. 
그런데 이 문제는, 중간값이 아니라 최댓값과 최솟값을 알아야 해서, 각 힙에서 최댓값/최솟값에 모두 접근할 수 있어야 하는 것 같아보였음.

그래서 고민을 하다가, 그냥 단순하게 접근해봤다. 최댓값을 delete할 때 사용할 최대 힙과 최솟값을 delete할 때 사용할 최소 힙을 둔다. 
이때, insert한 수를 반 나눠서 최대 최소 힙에 넣어주는 게 아니라, 그냥 둘 다 넣어준다. 그런 다음, 최댓값을 delete하려면 최대 힙에서, 
최솟값을 delete하려면 최소 힙에서 pop해준다. 근데 이러면 문제가 생긴다. 최대 힙에서 삭제한 숫자가 최소 힙에서는 삭제가 안 되는 문제가 발생. 
그래서, 이를 확인하기 위해 unordered_map을 사용했다. 어떠한 수를 key, 그 수의 개수를 value로 매핑하여, 어떠한 수가 다 삭제가 되었는지 
아닌지를 확인하는 것이다. 

우선 insert하는 부분은 쉽다. 최대 최소 힙에 다 push해주고, 매핑의 value를 1 증가시켜주면 된다.
그 다음 delete하는 부분에서, 최대 최소 힙에서 삭제(pop)를 해줄 때, 삭제하려고 시도하는 수(top)가 진짜 존재하는지, 아니면 다른 힙에서 이미 
삭제가 되었는지 확인해야 한다. 다른 힙에서 이미 삭제가 되었다면? 매핑의 value가 0일 것이다. 그렇지 않다면 그 수는 진짜 존재하는 것이다. 

마지막 출력 부분에서도 각 힙에서 똑같이 확인해준다. 가장 마지막으로 pop을 해준 뒤 top으로 올라온 수가 이미 삭제된 수일 수 있으므로.

이렇게 풀었는데, 다른 풀이를 검색해보니까 multiset을 사용하면 편한 문제였다. set(과 multiset)은 BST로 이루어져 있어서, iter를 통해 
첫 원소에 접근하면 최솟값, 마지막 원소에 접근하면 최댓값을 구할 수 있다. 걍 대놓고 이걸로 풀면 쉬운 문제였다.
*/