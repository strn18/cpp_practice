#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 1000000

using namespace std;

int arr[MAX];
vector<int> v; // v[i]: arr로부터 길이가 i+1인 LIS를 만들 때, 마지막(가장 큰) 수.

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  cin >> N;

  for(int i=0; i<N; i++)
    cin >> arr[i];
  
  v.push_back(arr[0]);

  for(int i=1; i<N; i++){
    if(arr[i] > v.back()){
      v.push_back(arr[i]);
    }
    else{
      int idx = lower_bound(v.begin(), v.end(), arr[i]) - v.begin();
      v[idx] = arr[i];
    }
  }

  cout << v.size();

  return 0;
}

/*
<algorithm>의 lower_bound를 처음 써본 문제. 원래 LIS는 DP를 이용하여 O(N^2)으로 풀었었는데, 이 문제는 N이 최대 100만이라 그걸로 풀 수 없다. 
그래서 어떻게 푸나 오래 고민하다가 결국 풀이를 찾아봤다. https://seungkwan.tistory.com/8 여기를 참고했는데, 핵심은 벡터(여기서는 v)를 사용하는 
것이다. v[i]는 arr로부터 길이가 i+1인 LIS를 만들 때, 마지막(가장 큰) 수이다. 단순히 LIS를 의미하는 게 아님에 주의. 자세한 설명은 링크 ㄱㄱ.
28행에서, 값이 arr[i] 이상이면서 처음 등장하는 위치를 찾기 위해 원래는 이분 탐색을 직접 구현해서 써왔는데, 이번에는 풀이에 나온 대로 
lower_bound를 사용했다. 1 2 2 3 3 4 5 가 있을 때, 거기서 숫자 3의 lower_bound는? 인덱스 3인 위치다. 숫자 3의 upper_bound는? 인덱스 5인 위치다. 
즉 lower_bound는 넣을 수 있는 가장 빠른 위치이고, upper_bound는 가장 마지막 위치라고 보면 된다. 
하여튼 이걸 써서 arr[i]를 넣을 위치(arr[i]보다 값이 크거나 같으면서 가장 빠른 위치)를 찾아 그 인덱스 값을 idx에 넣고, v[idx]에 arr[i]를 넣어 
v를 정의에 맞게 갱신해줬다. 
*/