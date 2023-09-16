#include <iostream>
#include <queue>
#include <cstring>
#define MAX 100000

using namespace std;

bool visited[MAX+1];

bool outOfBound(int n);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, K, ansTime, ansCount = 0;
  queue<pair<int, int>> Q;

  cin >> N >> K;

  Q.push({N, 0});

  while(!Q.empty()){
    int curPos, curTime;

    curPos = Q.front().first;
    curTime = Q.front().second;

    Q.pop();

    if(curPos == K){
      if(ansCount == 0){
        ansTime = curTime;
        ansCount = 1;
      }
      else if(ansTime == curTime) ansCount++;
    }

    visited[curPos] = true;

    if(!outOfBound(curPos - 1) && !visited[curPos - 1]) Q.push({curPos - 1, curTime + 1});
    if(!outOfBound(curPos + 1) && !visited[curPos + 1]) Q.push({curPos + 1, curTime + 1});
    if(!outOfBound(curPos * 2) && !visited[curPos * 2]) Q.push({curPos * 2, curTime + 1});
  }

  cout << ansTime << '\n' << ansCount;

  return 0;
}

bool outOfBound(int n){
  if(n < 0 || MAX < n) return true;
  else return false;
}