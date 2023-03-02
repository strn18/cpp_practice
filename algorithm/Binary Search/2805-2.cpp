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

/*
2805를 이진탐색으로 다시 풀어봤는데, 좀 헷갈렸다. start와 end에 대해서 이진탐색을 실시하는데, 그 사이에서 어떤 값을 찾나면, i 높이에서 나무들을
잘랐을 때 얻는 나무가 M 이상이도록 하는 가장 큰(높은) i를 찾아야 한다. 그래서 처음에는 start=0, end=나무 높이 최댓값. 으로 잡고 이진탐색을
실시하였다. 이때 mid를 잡아서, mid에서 얻는 나무가 M 이하면 start와 mid에 대해 다시 이진탐색을 하고, M 미만이면 mid+1과 end에 대해서 실시한다.
start와 end가 같아지면 start를 리턴한다. 예제로 주어진 것도 다 맞아서 맞는 줄 알았는데 틀렸다.

고민을 좀 해보니, else문(33행)이 문제였다. 예를 들어, 0~4에 대해 이진탐색을 쳤다고 하자. 이때 답이 2이고, 2 높이에서 잘랐을 때 얻는 나무들이
M 초과라면, 처음에는 mid는 2로 잡았을 것이고, get_tree(2)가 M보다 커서 else문에 해당이 되니깐 3~4에 대해 이진탐색을 쳤을 것이다. 그런데 그 다음,
이번엔 mid가 3이고, get_tree(3)은 M보다 작다. 그러면 if문에 해당이 되니깐 3~3에 대해 이진탐색을 치고, 최종적으로 3을 리턴한다. 답이 틀리게 됨.

이걸 잘 보완해서 제출하니 맞았다. else문에 해당이 될 때는, 바로 binary_search 값을 재귀로 리턴하는 게 아니라, 지금의 값(mid)이 답일 수 있으니,
그것과 mid+1~end에 대해서 재귀를 쳤을 때의 값을 비교해서 더 큰(높은) 값을 리턴한다. 만약 mid+1~end에 답이 없을 경우(그 범위에서 나무를 자르면
다 M 보다 작을 경우), 27행에 의해 -1을 리턴하니깐 mid를 리턴하게 된다.
*/