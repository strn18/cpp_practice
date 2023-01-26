#include <iostream>
#include <vector>
#define MAX 10000

using namespace std;

int answer = 0;
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
    }
  }

  printf("%d", answer);

  return 0;
}

void dfs(int w, int prev, int cur){
  if(edge[cur].size() == 1){
    answer = max(answer, w);
    return;
  }

  for(int i=0; i<edge[cur].size(); i++){
    if(edge[cur][i].first == prev) continue;
    dfs(w+edge[cur][i].second, cur, edge[cur][i].first);
  }
}

/*
많이 고민했고, 어려웠던 dfs 문제. 어떠한 노드에서 다른 노드까지의 경로값 중 가장 큰 값을 찾는 문제이다. 
나는 우선, 두 노드는 당연히 리프 노드가 되어야 최댓값을 가질 것으로 보았다(가중치가 양수니깐). 어떻게 풀지 이리저리 고민하다가, 그냥 단순하게
dfs를 쓰기로 했다. 근데 어떠한 리프 노드에서 시작해서 dfs를 칠 때, 시간복잡도는 O(V+E)로, O(2만)정도가 나온다. 그리고 리프 노드가 몇 개일지는
알 수 없으나, 최대 1만 개 정도일 수 있기에, 각 리프 노드를 시작으로 dfs 쳐주는 걸 모두 해준다고 하면, 총 시간복잡도가 O(1만) * O(2만) = 2억
정도로, 시간이 2초로 넉넉하긴 하지만 아마 시간초과가 나지 않을까 싶었다. 근데 계속 고민만 하느니 일단 뭐라도 해보는 게 나을 것 같아서 dfs로 해봄.

어떠한 노드에서 다른 노드로 뻗어나가는 dfs 함수를 정의했다. 이때 w는 지금까지의 가중치, prev는 바로 이전 노드의 번호, cur는 이번 노드의 번호이다.
만약 이번 노드의 간선이 한 개라면, 이번 노드는 리프 노드이다. 그렇기에, 리프 노드를 찾은 거니깐 지금까지의 가중치(맨 처음 시작한 리프 노드에서
지금 리프 노드에 오기까지의 가중치)로 answer를 갱신한다. 만약 간선이 두 개 이상이라면, 모든 간선을 돌아본다. 이때 이전 노드는 방문할 필요 없으니,
43행에서 continue 해준다. 그렇지 않다면, 지금까지의 가중치(w)에 다음 노드로의 가중치를 더해준 값을 인자로 넣어주면서, 다음 노드에서 dfs를 
시작해주면 된다. 

그리고 이 dfs를 모든 리프 노드에 대해 시작해줘야하므로, 25행에서 모든 노드를 돌면서, 그 노드의 간선이 하나일 경우(=그 노드가 리프 노드), 그 노드의
다음 노드에서 dfs를 시작해준다.

당연히 시간초과가 날 줄 알았는데, 380ms 정도로 그래도 넉넉하게 맞았다(첫번째 제출 때는 틀렸는데, 노드가 한 개일 때 답을 0으로 출력해야 하는데
answer의 초깃값을 -1로 해서 틀렸음). 근데 다른 사람들 풀이 보니까 한자리수ms라서, 다른 풀이 참고하고 새로 풀어보기로 함.
*/