#include <iostream>
#include <queue>
#include <cstring>
#define MAX 100000

using namespace std;

int fastestTime[MAX+2]; //  fastestTime[i]: i 위치로의 최단시간이 몇 초인지. 
long long sameCount[MAX+2]; // sameCount[i]: i 위치로 최단시간으로 오는 방법이 몇 개인지.

bool outOfBound(int n);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, K;
  bool foundFlag = false;
  queue<pair<pair<int, int>, int>> Q;

  cin >> N >> K;

  memset(fastestTime, -1, sizeof(fastestTime));

  sameCount[MAX+1] = 1;

  Q.push({{MAX+1, N}, 0});

  while(!Q.empty()){
    int prevPos, curPos, curTime;

    prevPos = Q.front().first.first;
    curPos = Q.front().first.second;
    curTime = Q.front().second;

    Q.pop();

    if(curPos == K) foundFlag = true;
    else if(foundFlag && curTime > fastestTime[K]) break;

    if(fastestTime[curPos] == -1){
      fastestTime[curPos] = curTime;
      sameCount[curPos] = sameCount[prevPos];

      if(!outOfBound(curPos - 1)) Q.push({{curPos, curPos - 1}, curTime + 1});
      if(!outOfBound(curPos + 1)) Q.push({{curPos, curPos + 1}, curTime + 1});
      if(!outOfBound(curPos * 2)) Q.push({{curPos, curPos * 2}, curTime + 1});
    }
    else if(fastestTime[curPos] == curTime){
      sameCount[curPos] += sameCount[prevPos];
    }
  }

  cout << fastestTime[K] << '\n' << sameCount[K];

  return 0;
}

bool outOfBound(int n){
  if(n < 0 || MAX < n) return true;
  else return false;
}

/*
쫌 까다롭게 느껴졌던 문제... 최단시간으로 N -> K로 가는 경우의 수가 x일 때, x가지 경우를 모두 bfs를 통해 센다면 시간초과가 날 것이라고 생각했다. 
그래서 중복을 최대한 피해주기 위해, 다음과 같은 방법을 사용했다. 

fastestTime[curPos]가 -1이라면? curPos 위치로는 이번 원소 때 처음 온 것이다(41행). 그러므로 curTime을 할당해주고, 이번 원소가 담고 있는 경우의 
수인 sameCount[prevPos]를 sameCount[curPos]에도 담아준다. 이게 뭔 소린지 모르겠다면 밑 문단부터 읽어보기.

fastestTime[curPos]가 -1은 아니지만, curTime과 같다면(49행)? 앞선 원소에서, curTime초에 curPos 위치에 도달했던 것이다. 이번 원소도 마찬가지 
상황이다. 그런데 이번 원소에서도, 3가지 분기(-1, +1, *2)로 갈라진다면, 불필요한 탐색 과정이 늘어난다. 그러므로, curPos로 도달한 경우의 수만 
갱신해준다. 즉 sameCount[prevPos]를 sameCount[curPos]에 더해주는 것이다.

근데 몇 번 틀렸다. 왜 그랬냐면, 3가지 분기로 갈라지는 거는 41행에 해당할 때만 해주고, 49행에 해당할 때는 그냥 sameCount[curPos]만 갱신해주면 
되는데, 그걸 잘못 했음.

풀고 나니 풀이가 너무 복잡해보여서 찾아봤다. https://transferhwang.tistory.com/288 여기를 보니까, 시간복잡도를 다소 포기한 대신 그냥 쉽게 
푸는 방식이 있었음. 자세한 건 링크 참조. 12851-2로 제출하니 맞긴 했는데 시간이 더 걸렸다.

https://www.acmicpc.net/source/66710884 여기 보니까, 내 풀이랑 비슷한데 더 간결하게 쓴 코드가 있었다.
*/