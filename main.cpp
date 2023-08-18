#include <iostream>
#define MAX 100

using namespace std;

int board[MAX][MAX];
long long dp[MAX][MAX];

long long DP(int r, int c);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  cin >> N;

  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      cin >> board[i][j];
      dp[i][j] = -1;
    }
  }

  dp[0][0] = 1;

  cout << DP(N-1, N-1);

  return 0;
}

long long DP(int r, int c){
  if(dp[r][c] != -1) return dp[r][c];

  long long count = 0;

  for(int i=0; i<r; i++)
    if(board[i][c] == r-i) count += DP(i, c);
  
  for(int j=0; j<c; j++)
    if(board[r][j] == c-j) count += DP(r, j);
  
  return dp[r][c] = count;
}



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