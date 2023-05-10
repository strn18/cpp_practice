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

/*
기본 최소 스패닝 트리 문제. 크루스칼 알고리즘(분리집합)으로 풀었다.

어렵진 않았음. 우선 모든 간선들을 가중치를 기준으로 오름차순 정렬한다. 그 다음 앞에서부터 그리디하게 보면서, 만약 간선이 {c, {a, b}}일 때
(c는 cost, a와 b는 간선의 두 정점), a와 b가 같은 component에 있으면 패스하고 그렇지 않으면 그 간선을 고른다(비용 갱신). 그런 식으로 총 N-1개의
간선을 고르면 끝. 더 고르면 무조건 사이클이 한 개는 생기니까 더 고를 필요 없다.

union이랑 find 함수만 잘 구현하면 되었음. 
*/