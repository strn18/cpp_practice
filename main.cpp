// #include <iostream>

// using namespace std;

// int main(){
//   ios_base::sync_with_stdio(false);
//   cin.tie(NULL);

//   return 0;
// }

// #include <iostream>
// #include <vector>
// #define MAX 262144
// #define INF 100000001

// using namespace std;

// int leaf_size;

// int num[MAX];
// pair<int, int> tree[MAX*2]; // {최솟값, 최댓값}

// void construct(int N);
// pair<int, int> find_val(int L, int R, int node_num, int node_L, int node_R);

// void init(int N, int mValue[]){
//   for(int i=0; i<N; i++)
//     num[i+1] = mValue[i];
  
//   construct(N);
// }

// void add(int M, int mValue[]){
  
// }

// void erase(int mFrom, int mTo){
  
// }

// int find(int K){
  
// }

// void construct(int N){
//   leaf_size = MAX;

//   for(int i=0; i<N; i++)
//     tree[leaf_size + i] = {num[i+1], num[i+1]};
  
//   for(int i=leaf_size+N; i<leaf_size*2; i++)
//     tree[i] = {INF, -1};

//   for(int i=leaf_size-1; i>=1; i--){
//     tree[i].first = min(tree[i*2].first, tree[i*2 + 1].first);
//     tree[i].second = max(tree[i*2].second, tree[i*2 + 1].second);
//   }
// }

// pair<int, int> find_val(int L, int R, int node_num, int node_L, int node_R);

// int main(){

// }