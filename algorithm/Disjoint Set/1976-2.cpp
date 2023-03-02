#include <iostream>
#define MAX 200

using namespace std;

int parent[MAX+1];

int find_root(int u);
void union_root(int u, int v);

int main(){
  int N, M, info, city, city_root;
  bool flag = true;

  scanf("%d %d", &N, &M);
  
  for(int i=1; i<=N; i++)
    parent[i] = i;

  for(int i=1; i<=N; i++){
    for(int j=1; j<=N; j++){
      scanf("%d", &info);
      if(info == 1) union_root(i, j);
    }
  }

  scanf("%d", &city);
  city_root = find_root(city);
  for(int i=1; i<M; i++){
    scanf("%d", &city);
    if(find_root(city) != city_root) flag = false;
  }

  printf("%s", flag ? "YES" : "NO");

  return 0;
}

int find_root(int u){
  if(parent[u] == u) return u;

  return parent[u] = find_root(parent[u]);
}

void union_root(int u, int v){
  int root_u = find_root(u);
  int root_v = find_root(v);

  if(root_u == root_v) return;

  parent[root_u] = root_v;
}

/*
1976을 분리집합으로 다시 한 번 풀어봄. find와 union만 간단하게 구현하면 됐다.
*/