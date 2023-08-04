// Segment Tree 연습 - 2(14. 세그먼트 트리)
#include <iostream>
#define MAX 131072

using namespace std;

long long tree[MAX*2];
int num[MAX];

int leaf_num;

void construct(int n);
void update(int idx, int val);
long long find(int L, int R, int node_num, int node_L, int node_R);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    int n, q;

    cin >> n >> q;

    for(int i=0; i<n; i++){
      cin >> num[i];
      if(i%2 == 1) num[i] *= -1;
    }

    construct(n);

    cout << '#' << t << ' ';

    while(q--){
      int a, b, c;

      cin >> a >> b >> c;

      if(a == 0) update(b, c);
      else{
        long long ans = find(b, c, 1, 0, leaf_num);
        cout << (b%2 == 0 ? ans : -ans) << ' ';
      }
    }

    cout << '\n';
  }

  return 0;
}

void construct(int n){
  leaf_num = 1;

  while(leaf_num < n) leaf_num *= 2;

  for(int i=0; i<n; i++)
    tree[leaf_num + i] = num[i];
  
  for(int i=leaf_num+n; i<leaf_num*2; i++)
    tree[i] = 0;

  for(int i=leaf_num-1; i>=1; i--)
    tree[i] = tree[i*2] + tree[i*2 + 1];
}

void update(int idx, int val){
  idx += leaf_num;

  tree[idx] = val;
  if(idx%2 == 1) tree[idx] *= -1;

  while(idx > 1){
    idx /= 2;
    tree[idx] = tree[idx*2] + tree[idx*2 + 1];
  }
}

long long find(int L, int R, int node_num, int node_L, int node_R){
  if(node_R <= L || R <= node_L) return 0;
  if(L <= node_L && node_R <= R) return tree[node_num];

  int mid = (node_L + node_R) / 2;

  return find(L, R, node_num*2, node_L, mid) + find(L, R, node_num*2 + 1, mid, node_R);
}

/*
No_45보다 더 기초적인 세그먼트 트리 문제. 대충 보면 좀 까다로워보이지만, 사실 쉽다. 

쿼리 0은 그냥 update 하는 기본 쿼리니깐 넘어가고,
쿼리 1은? 1 L R이 주어졌다면, num[L] - num[L+1] + num[L+2] ... num[R-1] 이렇게 더하고 빼고 더하고 빼고 해주면 된다. 이걸 어떻게 구할까?

그냥 애초에 28행에서 배열을 입력받을 때, 인덱스가 짝수라면 그대로 수를 입력받아 num에 넣고, 홀수라면 -1을 곱해서 num에 넣어주면 된다. 
그런 다음, 세그먼트 트리는 일반적인 구간 합 세그먼트 트리 형태로 구성한다. 그렇게 한다면, 세그먼트 트리에서 [A, B)의 범위를 갖는 노드의 
A가 짝수라면 num[A] - num[A+1] + num[A+2] ... num[B-1] 이거고, A가 홀수라면 -num[A] + num[A+1] - num[A+2] ... num[B-1] 이거다.
이를 이용하여, 쿼리 1 L R이 주어졌을 때, L이 짝수라면 그냥 [L, R) 범위의 세그먼트 트리를 find로 찾아 출력하면 되고, L이 홀수라면 그 값에 
-1을 곱해서 출력하면 된다.
*/