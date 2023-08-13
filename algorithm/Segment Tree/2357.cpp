#include <iostream>
#include <vector>
#define MAX 131072 // 10만 이상인 첫번째 2의 제곱수
#define INF 1000000001

using namespace std;

int leaf_size;

int num[MAX];
pair<int, int> tree[MAX*2];

void construct(int N);
pair<int, int> find(int L, int R, int node_num, int node_L, int node_R); // {최솟값, 최댓값} 리턴.

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;

  cin >> N >> M;

  for(int i=1; i<=N; i++)
    cin >> num[i];

  construct(N);
  
  while(M--){
    int a, b;
    pair<int, int> ans;

    cin >> a >> b;

    ans = find(a, b, 1, 1, leaf_size);

    cout << ans.first << ' ' << ans.second << '\n';
  }

  return 0;
}

void construct(int N){
  leaf_size = 1;

  while(leaf_size < N) leaf_size *= 2;

  for(int i=leaf_size; i<leaf_size+N; i++)
    tree[i] = {num[i-leaf_size + 1], num[i-leaf_size + 1]};

  for(int i=leaf_size+N; i<leaf_size*2; i++)
    tree[i] = {INF, 0};
  
  for(int i=leaf_size-1; i>=1; i--){
    tree[i].first = min(tree[i*2].first, tree[i*2 + 1].first);
    tree[i].second = max(tree[i*2].second, tree[i*2 + 1].second);
  }
}

pair<int, int> find(int L, int R, int node_num, int node_L, int node_R){
  if(node_R < L || R < node_L) return {INF, 0};
  if(L <= node_L && node_R <= R) return tree[node_num];

  int mid = (node_L + node_R) / 2;

  pair<int, int> left = find(L, R, node_num*2, node_L, mid);
  pair<int, int> right = find(L, R, node_num*2 + 1, mid+1, node_R);

  return {min(left.first, right.first), max(left.second, right.second)};
}

/*
어렵지 않은 세그먼트 트리 문제. 구간의 최솟값/최댓값을 찾는 게 아닌, 둘 다 모두 찾는다고 생각하면 된다.
*/