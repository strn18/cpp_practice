#include <iostream>
#define MAX 1048576
#define MOD 1000000007

using namespace std;

long long num[MAX];
long long tree[MAX*2] = {0};

int leaf_num = 1;

void construct(int n);
void update(int idx, int val);
long long find(int L, int R, int node_num, int node_L, int node_R);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, K;

  cin >> N >> M >> K;

  for(int i=1; i<=N; i++)
    cin >> num[i];

  construct(N);
  
  for(int i=0; i<M+K; i++){
    int a, b, c;

    cin >> a >> b >> c;

    if(a == 1) update(b, c);
    else cout << find(b, c, 1, 1, leaf_num) << '\n';
  }  

  return 0;
}

void construct(int n){
  while(leaf_num < n) leaf_num *= 2;

  for(int i=0; i<n; i++)
    tree[leaf_num + i] = num[i+1];

  for(int i=leaf_num-1; i>=1; i--)
    tree[i] = (tree[i*2] * tree[i*2 + 1]) % MOD;
}

void update(int idx, int val){
  idx += (leaf_num-1);
  tree[idx] = val;

  while(idx > 1){
    idx /= 2;
    tree[idx] = (tree[idx*2] * tree[idx*2 + 1]) % MOD;
  }
}

long long find(int L, int R, int node_num, int node_L, int node_R){
  if(node_R < L or R < node_L) return 1;
  if(L <= node_L and node_R <= R) return tree[node_num];

  int mid = (node_L+node_R)/2;

  return (find(L, R, node_num*2, node_L, mid) * find(L, R, node_num*2 + 1, mid+1, node_R)) % MOD;
}

/*
2042랑 거의 비슷한 세그먼트 트리 문제. 구간 곱을 구하는 것만 빼면 동일함.
*/