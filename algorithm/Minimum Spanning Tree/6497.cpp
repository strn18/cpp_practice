#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 200000

using namespace std;

int parent[MAX];

int find_root(int x);
void union_root(int x, int y);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int m, n;

  while(true){
    int cost_sum = 0;
    int cost_count = 0, edge_count = 0;
    vector<pair<int, pair<int, int>>> edge;

    cin >> m >> n;

    if(m == 0) break;

    for(int i=0; i<m; i++)
      parent[i] = i;

    for(int i=0; i<n; i++){
      int x, y, z;

      cin >> x >> y >> z;

      cost_sum += z;

      edge.push_back({z, {x, y}});
    }

    sort(edge.begin(), edge.end());

    for(int i=0; edge_count<m-1; i++){
      int a = edge[i].second.first;
      int b = edge[i].second.second;
      int cost = edge[i].first;

      if(find_root(a) == find_root(b)) continue;

      union_root(a, b);
      cost_count += cost;
      edge_count++;
    }

    cout << cost_sum - cost_count << '\n';
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
그냥 기본 MST 문제. 크루스칼(유니온 파인드)이 편해서 그걸로 풀었다. 별다른 건 없고, 그냥 일반적인 MST 문제는 가중치의 합(최소가 되도록 하는)을
구하고 출력하는데, 이 문제는 "총 간선 가중치 - 선택한 간선 가중치의 합"을 해줘야 함(절약한 만큼을 출력해야 하기 때문). 그거 빼면 별 거 없다.
*/