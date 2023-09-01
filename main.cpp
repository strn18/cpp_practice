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