// Segment Tree 연습 - 1(14. 세그먼트 트리)
#include <iostream>
#define MAX 131072
#define INF 2100000000

using namespace std;

typedef struct{int min_val, max_val;} info;
info tree[MAX*2];

int num[MAX];

int leaf_size; // num[i]는 tree[leaf_size + i]에 담긴다.

void construct(int n);
void update(int idx, int val);
info find(int L, int R, int node_num, int node_L, int node_R); // tree[node_num]은 num[node_L], num[node_R-1]을 커버함.

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    int n, q;

    cin >> n >> q;

    for(int i=0; i<n; i++)
      cin >> num[i];

    construct(n);

    cout << '#' << t << ' ';

    while(q--){
      int a, b, c;

      cin >> a >> b >> c;

      if(a==0) update(b, c);
      else{
        info ans = find(b, c, 1, 0, leaf_size);
        cout << ans.max_val - ans.min_val << ' ';
      }
    }

    cout << '\n';
  }

  return 0;
}

void construct(int n){
  leaf_size = 1;

  while(leaf_size < n) leaf_size *= 2;

  for(int i=0; i<n; i++)
    tree[leaf_size + i] = {num[i], num[i]};

  for(int i=leaf_size+n; i<2*leaf_size; i++)
    tree[i] = {INF, -INF};
  
  for(int i=leaf_size-1; i>=1; i--){
    tree[i].min_val = min(tree[i*2].min_val, tree[i*2 + 1].min_val);
    tree[i].max_val = max(tree[i*2].max_val, tree[i*2 + 1].max_val);
  }
}

void update(int idx, int val){
  idx += leaf_size;

  tree[idx] = {val, val};

  while(idx > 1){
    idx /= 2;
    tree[idx].min_val = min(tree[idx*2].min_val, tree[idx*2 + 1].min_val);
    tree[idx].max_val = max(tree[idx*2].max_val, tree[idx*2 + 1].max_val);
  }
}

info find(int L, int R, int node_num, int node_L, int node_R){
  if(node_R <= L || R <= node_L) return {INF, -INF};
  if(L <= node_L && node_R <= R) return tree[node_num];

  int mid = (node_L+node_R)/2;

  info left = find(L, R, node_num*2, node_L, mid);
  info right = find(L, R, node_num*2 + 1, mid, node_R);

  return {min(left.min_val, right.min_val), max(left.max_val, right.max_val)};
}

/*
세그먼트 트리 변형 문제. 기초 세그먼트 트리 문제는 수열의 특정 구간의 합 또는 곱 뭐 이런 걸 트리에 담겠지만, 이 문제는 특정 구간의 
최댓값 - 최솟값을 다루게 된다. 그렇기에, 최댓값을 담는 트리와 최솟값을 담는 트리를 따로 만들어도 되었겠지만, 구조체를 써서 한 트리에 담았다. 

find 함수를 통해 해당 구간의 최솟값과 최댓값을 ans에 담은 다음, 그 차를 출력하도록 했다(46행).

일반적인 세그먼트 트리 문제와 크게 다른 것은 없었고, 특정 구간의 합을 구하는 문제라면 find 함수에서 그냥 반띵한 두 구간의 리턴값을 더해서 
리턴하는 방식이었겠지만, 이 문제에서는 각 구간의 최솟값/최댓값을 담은 뒤(91, 92행) 비교해서 구조체 형태로 리턴하도록 하였다.

마지막에 제출하다 틀렸는데, 매우 어이없게도 개행을 #1을 출력하기 전에 넣는 걸로 짜서.. ㅎㅎ 이런 걸로 틀리게 하는 건 처음 봄.
*/