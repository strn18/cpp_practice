#include <iostream>
#include <algorithm>
#define MAX 1000000

using namespace std;

bool Compare(int a, int b){
  return a > b;
}

int tree[MAX];

int main(){
  int N, M, ans = -1;

  scanf("%d %d", &N, &M);
  for(int i=0; i<N; i++)
    scanf("%d", &tree[i]);

  sort(tree, tree+N, Compare);
  
  for(int second=1; second<N; second++){
    if(tree[0] == tree[second]) continue;

    if((tree[0]-tree[second])*second >= M){
      int temp = M/second;
      if(temp*second < M) temp++;
      ans = tree[0] - temp;
      break;
    }
    else{
      M -= (tree[0]-tree[second])*second;
      tree[0] = tree[second];
    }
  }

  if(ans == -1){
    int temp = M/N;
    if(temp*N < M) temp++;
    ans = tree[0] - temp;
  }

  printf("%d", ans);

  return 0;
}

/*
크게 어렵지는 않았던 문제. 나는 그냥 나무를 내림차순으로 정렬해두고, 가장 큰 나무와 두번째로 큰 나무를 비교해서, 가큰나를 두큰나의 높이까지 잘라서
얻는 양이 M 미만이면 가큰나를 두큰나의 높이까지 자르고, M을 갱신한다(31행). 만약 M 이상이면 얼만큼 잘라야 가장 덜 자르면서 M 이상 얻을 수 있는지
계산해서, 답을 구한다(25행). 코드에서는 첫번째 나무(tree[0])과 두번째로 큰 나무(tree[second])를 비교하고, 가큰나를 잘라서 높이 줄이는 것도
tree[0]에 대해서만 했지만, 실제로는 가장 큰 나무들을 모두 잘랐다고 생각하며 M을 갱신한다(32행에서, second를 곱하는 이유가 바로 그거임. second가
곧 가장 큰 나무들의 개수이기 때문).
이 방식으로 했는데 ans가 안 구해졌다면, 모든 나무의 높이가 같은 상태이므로, 25행과 비슷한 방식을 모든 나무에 대해 다시 한 번 해준다.

나는 이렇게 풀었는데, 풀이를 찾아보니 다들 이진탐색으로 풀었다. 나처럼 계산해가면서 풀지 않고, 가장 큰 나무의 높이를 end라고 하면, 0부터 end에
대해 이진탐색을 실시하면서, 얼만큼 잘라야 M 이상 얻으면서 제일 적게 자르게 되는 i를 구한다. 즉, 0와 end의 중간값을 mid로 잡고, 나무들을 mid까지
잘랐을 때 얻는 양을 계산하여, 그게 M 이상이면 mid+1부터 end에 대해 다시 이진탐색을 한다. 만약 M 미만이면, 0부터 mid-1에 대해 다시 이진탐색 한다.
이걸 반복하여 답을 구한다.
*/