#include <iostream>
#include <vector>
#define MAX 10000

using namespace std;

int answer = 0, end_point = 0;
vector<pair<int, int>> edge[MAX+1];

void dfs(int w, int prev, int cur);

int main(){
  int n;

  scanf("%d", &n);

  for(int i=0; i<n-1; i++){
    int a, b, c;

    scanf("%d %d %d", &a, &b, &c);
    edge[a].push_back({b, c});
    edge[b].push_back({a, c});
  }

  for(int i=1; i<=n; i++){
    if(edge[i].size() == 1){
      dfs(edge[i][0].second, i, edge[i][0].first);
      break;
    }
  }

  if(end_point)
    dfs(edge[end_point][0].second, end_point, edge[end_point][0].first);

  printf("%d", answer);

  return 0;
}

void dfs(int w, int prev, int cur){
  if(edge[cur].size() == 1){
    if(w > answer){
      answer = w;
      end_point = cur;
    }
    return;
  }

  for(int i=0; i<edge[cur].size(); i++){
    if(edge[cur][i].first == prev) continue;
    dfs(w+edge[cur][i].second, cur, edge[cur][i].first);
  }
}

/*
https://codingwell.tistory.com/61 여기 코드 참고하여 다시 풀어보았다. 
그냥 무작정 모든 리프 노드에 대해서 dfs를 시작하는 게 아니라, 우선 아무 노드에서 시작한다. 그 다음, answer를 최댓값으로 갱신할 때마다, 그 최종
도착 리프 노드의 번호를 기록해둔다. 그렇게 해서 탐색이 끝나고 나면, 기록해둔 리프 노드가 바로 원의 지름을 이루는 두 노드 중에 하나이다.
ㄷㄷ 천잰가? 이걸 어떻게 알았지;; 어쨌든 이렇게 해서 탐색을 한 번 하고, 그 리프 노드를 시작으로 다시 한 번 dfs를 쳐주면, 답을 구하게 된다.

그래서 나도 이거에 맞게 좀 수정해서 제출했는데, 틀렸다. 좀 생각해보니, 첫 dfs를 칠 때, 1번 노드의 0번째 간선으로 연결된 노드를 시작으로 삼았는데,
이렇게 하면 그쪽 가지에 원의 지름을 이루는 두 노드가 없다면, 걔네를 찾을 수 없다. 즉 위 코드에서 한 것처럼, 아예 1번 노드 자체를 시작으로 해야함.
근데 내 코드랑 그 코드랑 좀 달라서, 내가 그렇게 하면 1번 노드가 리프 노드일 때 41행에 걸려서 바로 나와버리는 문제가 있기도 해서, 그냥 내 코드에
맞게, 아예 1~n번 노드를 돌면서, 리프 노드를 찾아서 dfs를 쳐주는 식으로 했다. 어차피 그렇게 해봤자 연산 별로 안 늘어나니깐.. 위 코드에서 visited
배열 초기화 해주는 거랑 삐까칠듯

어쨌든 그렇게 해서 원의 지름을 이루는 노드 하나를 찾고, 그 리프 노드를 대상으로 다시 dfs를 쳐주면, 원의 지름을 구하게 된다. 
만약 못 찾았다면, 노드가 1개라는 것이니까 dfs를 안 쳐주면 된다.

근데 첫 번째 풀이에서 시간초과는 왜 안 났을까? 어쨌든 앞으로도, 시간초과가 날 것 같아도 그냥 일단 코드 짜보는 게 낫겠다.
*/