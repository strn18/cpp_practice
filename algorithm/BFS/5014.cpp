#include <iostream>
#include <queue>
#define MAX 1000000

using namespace std;

bool visited[MAX+1] = {false};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int F, S, G, U, D, ans = MAX;
  queue<pair<int, int>> Q; // {현재 층, 버튼 누른 횟수}

  cin >> F >> S >> G >> U >> D;

  Q.push({S, 0});

  while(!Q.empty()){
    int n = Q.size();

    while(n--){
      int cur = Q.front().first;
      int count = Q.front().second;

      if(cur == G){
        cout << count;
        return 0;
      }

      Q.pop();

      if(visited[cur]) continue;

      visited[cur] = true;
      if(cur+U <= F && !visited[cur+U]) Q.push({cur+U, count+1});
      if(1 <= cur-D && !visited[cur-D]) Q.push({cur-D, count+1});
    }
  }

  cout << "use the stairs";

  return 0;
}

/*
쉬운 bfs(queue) 문제. 처음 층(S)에서 시작해서, 위로 U층 or 아래로 D층 내려가는 걸 bfs로 모두 찾아보면 됨. 그러다가 G층에 도달하면 답을 출력하고,
끝까지 도달하지 못하면 uste the stairs를 출력. 이때, visited 배열을 사용하여 한 번 방문한(이전에 이미 도달한) 층에 다시 도달했을 경우, 쓸데없이
또 큐에 넣어주는 걸 하지 않도록 하였다.
*/