#include <iostream>
#define MAX 1000000

using namespace std;

int parent[MAX+1];
int root_rank[MAX+1];

int find_root(int u);
void union_root(int u, int v);

int main(){
  int n, m;

  scanf("%d %d", &n, &m);

  for(int i=1; i<=n; i++){
    parent[i] = i;
    root_rank[i] = 1;
  }
  
  for(int i=0; i<m; i++){
    int t, a, b;
    scanf("%d %d %d", &t, &a, &b);

    if(t == 0)
      union_root(a, b);
    else if(find_root(a) == find_root(b))
      printf("YES\n");
    else
      printf("NO\n");
  }

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

  // root_u를 root_v에 붙일 건데, root_u의 높이(rank)가 더 크면 안 됨
  if(root_rank[root_u] > root_rank[root_v])
    swap(root_u, root_v);
  
  parent[root_u] = root_v;
  // 두 root의 높이가 같았다면, root_v의 높이가 1 증가하게 됨(root_v에 붙였으니까)
  if(root_rank[root_u] == root_rank[root_v])
    root_rank[root_v]++;
}

void swap(int& a, int& b){
  int temp = a;
  a = b;
  b = temp;
}