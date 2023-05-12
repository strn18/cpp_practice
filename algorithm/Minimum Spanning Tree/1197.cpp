#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 10000

using namespace std;

int parent[MAX+1];

int find_root(int x);
bool union_root(int x, int y);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int V, E, edge_count = 0, weight_count = 0;
  vector<pair<int, pair<int, int>>> edge;

  cin >> V >> E;

  for(int i=1; i<=V; i++)
    parent[i] = i;

  for(int i=0; i<E; i++){
    int A, B, C;

    cin >> A >> B >> C;

    edge.push_back({C, {A, B}});
  }

  sort(edge.begin(), edge.end());

  for(int i=0; edge_count<V-1; i++){
    int a = edge[i].second.first;
    int b = edge[i].second.second;
    int c = edge[i].first;

    if(!union_root(a, b)) continue;

    edge_count++;
    weight_count += c;
  }

  cout << weight_count;

  return 0;
}

int find_root(int x){
  if(parent[x] == x) return x;

  return parent[x] = find_root(parent[x]);
}

bool union_root(int x, int y){
  int rx = find_root(x);
  int ry = find_root(y);

  if(rx == ry) return false;

  parent[rx] = ry;
  return true;
}

/*
1922랑 거의 비슷한 MST 기본 문제. union_root를 bool 형으로 한 것 빼고는 똑같이 풀었다. x, y의 root가 같으면 false를 리턴하고, 다르면 union
한 다음 true를 리턴한다. 이렇게 하면 35행 for문에서 간선을 고를 때, a와 b의 root가 같은지 확인한 후 union을 해줄 필요 없이 그냥 union_root만
해주면 되니까 좀 짧아짐.
*/