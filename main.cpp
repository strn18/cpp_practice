#include <iostream>
#define MAX 1000000

using namespace std;

long long N, M;
int tree[MAX];

int binary_search(int start, int end);
long long get_tree(int height);

int main(){
  int max_height = 0;

  scanf("%lld %lld", &N, &M);
  for(int i=0; i<N; i++){
    scanf("%d", &tree[i]);
    max_height = max(max_height, tree[i]);
  }

  printf("%d", binary_search(0, max_height));

  return 0;
}

int binary_search(int start, int end){
  if(start == end) return get_tree(start) >= M ? start : -1;

  int mid = (start+end)/2;

  if(get_tree(mid) < M)
    return binary_search(start, mid);
  else
    return max(mid, binary_search(mid+1, end));
}

long long get_tree(int height){
  long long count = 0;

  for(int i=0; i<N; i++)
    if(tree[i] > height)
      count += (tree[i] - height);

  return count;
}