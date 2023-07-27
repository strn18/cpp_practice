// [Professional] 고속도로 건설 2(5. 그래프)
#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 50000

using namespace std;

int find_root(int x);
void union_root(int x, int y);

int parent[MAX+1];

int main(){
  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    int N, M;
    vector<pair<int, pair<int, int>>> edge; // {비용, {출발, 도착}}

    cin >> N >> M;

    for(int i=1; i<=N; i++)
      parent[i] = i;

    for(int i=0; i<M; i++){
      int s, e, c;

      cin >> s >> e >> c;

      edge.push_back({c, {s, e}});
    }

    sort(edge.begin(), edge.end());

    int count = 1, total_cost = 0;

    for(int i=0; count<N; i++){
      int x = edge[i].second.first;
      int y = edge[i].second.second;

      if(find_root(x) == find_root(y)) continue;

      union_root(x, y);
      count++;
      total_cost += edge[i].first;
    }

    cout << '#' << t << ' ' << total_cost << '\n';
  }

  return 0;
}

int find_root(int x){
  if(parent[x] == x) return x;

  return parent[x] = find_root(parent[x]);
}

void union_root(int x, int y){
  int rx = find_root(x);
  int ry = find_root(y);

  parent[rx] = ry;
}

/*
얘도 No_18처럼 걍 MST 문제. 크루스칼로 풀었다.
*/