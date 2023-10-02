#include <iostream>
#include <queue>
#include <vector>
#define MAX 100000

using namespace std;

vector<int> adj[MAX+1];

bool visited[MAX+1] = {false};
vector<int> child[MAX+1];

int dp[MAX+1] = {0};

void bfs(int start);
int subTreeSize(int root);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, R, Q;

  cin >> N >> R >> Q;

  for(int i=0; i<N-1; i++){
    int U, V;

    cin >> U >> V;

    adj[U].push_back(V);
    adj[V].push_back(U);
  }

  bfs(R);

  while(Q--){
    int U;

    cin >> U;

    cout << subTreeSize(U) << '\n';
  }

  return 0;
}

void bfs(int start){
  queue<int> Q;

  Q.push(start);

  while(!Q.empty()){
    int cur = Q.front();

    Q.pop();

    visited[cur] = true;

    for(auto v: adj[cur]){
      if(visited[v]) continue;

      child[cur].push_back(v);
      Q.push(v);
    }
  }
}

int subTreeSize(int root){
  if(dp[root] != 0) return dp[root];

  dp[root] = 1;

  for(auto c: child[root])
    dp[root] += subTreeSize(c);

  return dp[root];
}

/*
트리의 노드가 10만 개, 쿼리가 10만 개이다. 그래서 우선 트리를 만들어놓고, 서브트리의 노드 개수를 세는 쿼리는 DP를 통해 해결할 수 있도록 했다. 
이렇게 하면, 쿼리가 10만 개여도 대략 O(10만) 이면 쿼리를 해결할 수 있다.

트리를 만드는 방식은 BFS로 풀었다. 루트에서 시작해서 BFS를 치면서, 벡터인 child를 채울 수 있도록 했다. 
근데 다른 풀이들 보니까, 대부분 DFS로 풀었다. 나처럼 1) BFS를 쳐서 트리 만들기. 2) DP로 서브트리의 노드 개수 세기. 이렇게 나누는 게 아니라, 
DFS로 트리를 만들면서 동시에 서브트리의 노드 개수도 세는 방식이었다. https://imnotabear.tistory.com/226
*/