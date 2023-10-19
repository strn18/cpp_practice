#include <iostream>
#include <vector>
#include <queue>
#define MAX 500

using namespace std;

vector<int> adj[MAX+1];

int bfs(int start, int maxDepth);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;

  cin >> n >> m;

  for(int i=0; i<m; i++){
    int a, b;

    cin >> a >> b;

    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  cout << bfs(1, 2);

  return 0;
}

int bfs(int start, int maxDepth){
  queue<pair<int, int>> Q;
  bool visited[MAX+1] = {false};
  int count = 0;

  Q.push({start, 0});
  visited[start] = true;

  while(!Q.empty()){
    int curNum = Q.front().first;
    int curDepth = Q.front().second;

    Q.pop();

    if(curDepth == maxDepth) return count;

    for(int i=0; i<adj[curNum].size(); i++){
      int nextNum = adj[curNum][i];

      if(!visited[nextNum]){
        Q.push({nextNum, curDepth + 1});
        visited[nextNum] = true;
        count++;
      }
    }
  }

  return count;
}

/*
걍 1번 노드를 시작으로 bfs를 쳐서, 1번 노드가 root일 때 depth가 2인 노드들까지만 세면 된다. 
*/