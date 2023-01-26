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