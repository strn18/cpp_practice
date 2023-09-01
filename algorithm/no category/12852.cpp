#include <iostream>
#include <queue>
#include <stack>
#define MAX 1000000

using namespace std;

int prevVal[MAX + 1] = {0};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  queue<pair<int, int>> Q; // 값, 횟수

  cin >> N;

  Q.push({N, 0});

  while(!Q.empty()){
    int curVal = Q.front().first;
    int curCalc = Q.front().second;

    Q.pop();

    if(curVal == 1){
      cout << curCalc << '\n';
      break;
    }

    if(curVal % 3 == 0 && !prevVal[curVal / 3]){
      Q.push({curVal / 3, curCalc + 1});
      prevVal[curVal / 3] = curVal;
    }
    if(curVal % 2 == 0 && !prevVal[curVal / 2]){
      Q.push({curVal / 2, curCalc + 1});
      prevVal[curVal / 2] = curVal;
    }
    if(!prevVal[curVal - 1]){
      Q.push({curVal - 1, curCalc + 1});
      prevVal[curVal - 1] = curVal;
    }
  }

  stack<int> nums;
  int cur = 1;

  while(true){
    nums.push(cur);

    if(cur == N) break;

    cur = prevVal[cur];
  }

  while(!nums.empty()){
    cout << nums.top() << ' ';
    nums.pop();
  }
  
  return 0;
}

/*
풀이랑 태그 보니까 다들 bottom-up dp로 풀었던데 나는 그냥 큐로 풀었다. 어차피 N의 범위가 100만이니까, 중복 체크 해주면서 N에서부터 시작해서 
연산 세 가지를 하고 큐에 넣어주는 걸 하면, 대충 100만 번 정도만 하게 된다. 그런 다음, 그동안 거쳐온 수를 출력하는 것은 prevVal 배열을 사용하여 
역으로 구했다. prevVal[i]: i라는 수를 만들기 직전의 수이다. 1부터 시작해서, prevVal[1], ... 이렇게 거꾸로 돌면서 스택에 넣어주고 다시 스택을 
출력하여 순서대로 출력되도록 했음.
*/