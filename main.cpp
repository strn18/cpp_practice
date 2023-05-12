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