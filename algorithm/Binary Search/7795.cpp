#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  while(T--){
    int N, M, ans = 0;
    vector<int> Asize, Bsize;

    cin >> N >> M;

    for(int i=0; i<N; i++){
      int size;

      cin >> size;

      Asize.push_back(size);
    }

    for(int i=0; i<M; i++){
      int size;

      cin >> size;

      Bsize.push_back(size);
    }

    sort(Bsize.begin(), Bsize.end());

    for(int i=0; i<N; i++)
      ans += lower_bound(Bsize.begin(), Bsize.end(), Asize[i]) - Bsize.begin();
    
    cout << ans << '\n';
  }

  return 0;
}
/*
처음에는, A와 B의 크기도 최대 2만인 줄 알았다. 그래서, int sizeB[2만 + 1] 이렇게 해놓고, sizeB[i]: B의 크기들 중에, i 이하인 것들의 개수. 
이렇게 해놨다. 그런 다음 A의 모든 크기(A[i])를 돌면서, ans += sizeB[A[i]-1]; 이렇게 해주면 A[i]보다 크기가 작은 것들의 개수를 쉽게 구할 수 
있다. 그리고 sizeB를 채우는 것도, 우선 B의 크기를 다 입력 받은 후에, sizeB[i] += sizeB[i-1] 이걸 i는 1부터 MAX까지 해주면 O(N)으로 채울 수 
있다.

그래서 냈는데 세그먼트 폴트 발생. 알고보니, A와 B의 크기는 그냥 양의 정수(아마 int 범위겠지)여서, sizeB의 인덱스가 2만을 넘어가니 에러가 뜬 것임. 
그래서 이분탐색으로 바꿨다. B의 크기들을 정렬해두고(Bsize에), A의 모든 크기(A[i])를 돌면서, Bsize에서 lower_bound를 해줘서 처음으로 A[i]의 이상이 
되는 곳의 인덱스를 찾는다. 그 인덱스 값이 곧 A[i]보다 작은 원소들의 개수임. 

제출하니 맞았다. https://2jinishappy.tistory.com/249 여기를 보니까, 투 포인터도 가능하다. A와 B의 크기롤 모두 정렬해놓고, 투 포인터로 
O(N)으로 풀 수 있음(정렬이 O(NlogN)이긴 해). 
*/