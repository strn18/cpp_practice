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

/*
쫌 쉽지 않았던 문제.. 생각나는 풀이법이 다 시간초과 나는 거라 힘들었다.

우선 그냥 단순하게, set[i]: i가 포함된 집합(의 원소들). 라고 두고, 푸는 것을 고민해봤다(파이썬으로).
0 i j가 주어졌을 때, a = set[i][::](얕은 복사를 위해), b = set[j][::]로 잡는다. 그 다음,
for i in a:
    set[i] += b
for i in b:
    set[i] += a
를 해준다. 왜냐? i가 포함된 집합(i집합)과 j가 포함된 집합(j집합)을 합치는 거니까, i집합(a)의 원소들 각각의 set값(집합)에 j집합(b)를 합쳐주고,
반대로도 해준다. 가령, 1과 2가 같은 집합, 3과 4가 같은 집합이면, set[1] = [1, 2], set[2] = [2, 1], set[3] = [3, 4], set[4] = [4, 3] 이렇게
되어 있을 거고(원소 순서는 노상관), 위의 연산을 쳐주면 set[1]과 set[2]에 [3, 4]를 합쳐주고, set[3]과 set[4]에 [1, 2]를 더해주게 된다.

이렇게 하면 확실히 맞긴 하겠지만, 너무 오래 걸린다. 가령 len(a) = 1만, len(b) = 1만 이라고 하면, a를 다 돌면서 각각의 원소의 set값에 또 b를
합쳐줘야하는데, 그것만 해도 1만(a의 크기) * 1만(b의 크기) 가 된다. 즉 무조건 시간초과라는 얘기..

C++로 푸는 것도, 포인터를 사용해서 푸는 것을 이리저리 고민해봤는데, 결국 못 풀었음. 그래서 결국 알고리즘 분류를 봤는데, 분리집합이었다.
분리집합은 10775번 문제를 풀 때 처음 접했었는데, 그거일 줄은 몰랐다.. 생각해보면 분리집합은 어떠한 노드가 속한 집합의 루트 노드를 알아내거나,
어떠한 노드의 다른 노드 각각이 속한 집합을 하나로 합칠 때 쓰기 좋은 기술인데, 대놓고 이 문제랑 똑같다.

그래서 10775번 소스코드랑, 거기에 달아놓은 링크 보면서 풀어서 맞을 수 있었다. 근데 10775에서는 뺐던 rank 계산 부분(union을 할 때 집합이
아래로 너무 길어지지 않도록 하는)을 두 번째 제출 때 넣어봤는데, 오히려 시간이 늘어났다. 아마 n이나 m이 그렇게 크지는 않아서, 그 부분을 
넣음으로써 줄어드는 시간보다 rank 계산하고 스왑하고 하는 것으로 인해 늘어나는 시간이 더 커서 그런듯.
*/