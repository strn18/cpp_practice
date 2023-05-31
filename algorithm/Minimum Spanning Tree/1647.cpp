#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 100000

using namespace std;

typedef struct{int a, b, c;} road;

vector<road> edge;
int parent[MAX+1];

bool compare(road x, road y);
int find_root(int x);
void union_root(int x, int y);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;
  int edge_count = 0, cost_count = 0;

  cin >> N >> M;

  for(int i=1; i<=N; i++)
    parent[i] = i;

  for(int i=0; i<M; i++){
    int A, B, C;

    cin >> A >> B >> C;

    edge.push_back({A, B, C});
  }

  sort(edge.begin(), edge.end(), compare);

  for(int i=0; edge_count<N-2; i++){
    int a = edge[i].a;
    int b = edge[i].b;
    int c = edge[i].c;

    if(find_root(a) == find_root(b)) continue;

    union_root(a, b);

    edge_count++;
    cost_count += c;
  }

  cout << cost_count;

  return 0;
}

bool compare(road x, road y){
  return x.c < y.c;
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
기초 MST 문제. 그냥 MST를 푼 다음에, 가장 가중치가 큰 간선만 제외해주면 됨. 즉 노드가 V개일 때, 원래는 V-1개 만큼의 간선을 추가하겠지만,
여기서는 V-2개 만큼만 추가해주고 for문을 break하면 됨(39행). 그거 말고는 그냥 MST 문제랑 똑같다.
*/