#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 1000

using namespace std;

int parent[MAX+1];

int find_root(int x);
void union_root(int x, int y);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, ans = 0, count = 0;
  vector<pair<int, pair<int, int>>> edge; // {c, {a, b}}

  cin >> N >> M;

  for(int i=1; i<=N; i++)
    parent[i] = i;

  for(int i=0; i<M; i++){
    int a, b, c;

    cin >> a >> b >> c;
    edge.push_back({c, {a, b}});
  }

  sort(edge.begin(), edge.end());

  for(int i=0; i<M; i++){
    int a = edge[i].second.first;
    int b = edge[i].second.second;
    int c = edge[i].first;

    if(find_root(a) == find_root(b)) continue;

    union_root(a, b);
    ans += c;
    if(++count == N-1) break;
  }

  cout << ans;

  return 0;
}

int find_root(int x){
  if(parent[x] == x) return x;

  return parent[x] = find_root(parent[x]);
}

void union_root(int x, int y){
  int rx = find_root(x);
  int ry = find_root(y);

  if(rx == ry) return;

  parent[ry] = rx;
}