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