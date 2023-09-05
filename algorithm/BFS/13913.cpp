#include <iostream>
#include <queue>
#include <stack>
#define MAX 100000

using namespace std;

bool visited[MAX+1] = {false};
int prevPos[MAX+1];

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, K, ans;
  queue<pair<int, int>> subin; // {위치, 시간}

  cin >> N >> K;

  subin.push({N, 0});
  visited[N] = true;

  while(true){
    pair<int, int> cur = subin.front();

    subin.pop();

    if(cur.first == K){
      ans = cur.second;
      break;
    }

    if(0 <= cur.first - 1 && !visited[cur.first - 1]){
      subin.push({cur.first - 1, cur.second + 1});
      visited[cur.first - 1] = true;
      prevPos[cur.first - 1] = cur.first;
    }
    if(cur.first + 1 <= MAX && !visited[cur.first + 1]){
      subin.push({cur.first + 1, cur.second + 1});
      visited[cur.first + 1] = true;
      prevPos[cur.first + 1] = cur.first;
    }
    if(cur.first * 2 <= MAX && !visited[cur.first * 2]){
      subin.push({cur.first * 2, cur.second + 1});
      visited[cur.first * 2] = true;
      prevPos[cur.first * 2] = cur.first;
    }
  }

  int curPos = K;
  stack<int> posHistory;

  while(curPos != N){
    posHistory.push(curPos);
    curPos = prevPos[curPos];
  }

  posHistory.push(N);

  cout << ans << '\n';

  while(!posHistory.empty()){
    cout << posHistory.top() << ' ';
    posHistory.pop();
  }

  return 0;
}

/*
1697 숨바꼭질 변형 문제. 똑같이 큐 써서 풀면 되고, prevPos 배열을 추가로 써서 어떠한 위치에 도달하기 직전의 위치가 무엇이었는지 기록하여, 
경로를 역으로 찾아갈 수 있게 했다.
*/