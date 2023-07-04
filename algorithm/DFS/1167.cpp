#include <iostream>
#include <vector>
#define MAX 100000

using namespace std;

bool visited[MAX+1] = {false};
int dist[MAX+1];
vector<pair<int, int>> adj[MAX+1];

void dfs(int start, int count);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int V, max_dist = 0, max_num = 0, ans = 0;

  cin >> V;

  for(int i=0; i<V; i++){
    int a, b, c;

    cin >> a;

    while(true){
      cin >> b;
      if(b == -1) break;
      cin >> c;
      adj[a].push_back({b, c});
    }
  }

  dfs(1, 0);

  for(int i=1; i<=V; i++){
    if(dist[i] > max_dist){
      max_dist = dist[i];
      max_num = i;
    }

    visited[i] = false;
  }

  dfs(max_num, 0);

  for(int i=1; i<=V; i++)
    ans = max(ans, dist[i]);

  cout << ans;

  return 0;
}

void dfs(int start, int count){
  visited[start] = true;
  dist[start] = count;

  for(int i=0; i<adj[start].size(); i++){
    int next = adj[start][i].first;
    
    if(!visited[next]) dfs(next, count+adj[start][i].second);
  }
}

/*
변형 dfs 문제. 

처음에는, 모든 정점에서 시작하여 다른 정점들로 가는 거리를 모두 구하고, 그 중에서 최댓값을 구해야하는 줄 알았다(플로이드-와샬 등을 사용하여).
근데, 정점이 최대 10만 개라 그렇게 하면 시간초과가 무조건 남. 그래서 생각해보니까, 어떠한 두 정점 A, B가 트리의 지름을 이룬다면, 다른 어떠한 정점
C에서 시작하여, 타 정점들로의 거리를 모두 구했을 때, 그 거릿값 중 가장 큰 값이 있다고 하자. 이때, C-A 또는 C-B가 반드시 최대 거릿값을 가진다. 즉
C와 가장 멀리 떨어진 노드는 반드시 A 또는 B이다. 왜인지는, 원을 그려보고 그 지름을 A와 B가 잇는다고 생각하고, 다른 정점들을 잘 그려보면 그렇다는
것을 알 수 있다. 그리고 참고로 주어진 건 그래프가 아니라 트리이기에 사이클이 없음.

어쨌든 이걸 갖고, dfs를 두 번 치면 풀 수 있다. 아무 정점(이 코드에서는 1번 노드에서 시작했음)에서 시작하는 dfs를 쳐서, 다른 노드들로의 거리(배열
dist에 담았다)를 구하고, 그 중 최댓값(max_dist)을 갖도록 1번 노드와 이어지는 노드(max_num번 노드)를 구한다. 그런 다음, 그 노드에서 시작하는 
dfs를 다시 한 번 친 후(거릿값은 dist를 재활용하여 거기에 다시 담았음), dist 중에서 최댓값(최대 거리. 즉 트리의 지름)을 구하면 그게 답이다.

1967번이랑 거의 똑같은 문제. 왠지 뭔가 쉽더라..
*/