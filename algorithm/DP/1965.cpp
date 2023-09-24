#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 1000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  int box[MAX];
  vector<int> v;

  cin >> N;

  for(int i=0; i<N; i++)
    cin >> box[i];

  v.push_back(box[0]);

  for(int i=1; i<N; i++){
    if(box[i] > v.back()) v.push_back(box[i]);
    else{
      int idx = lower_bound(v.begin(), v.end(), box[i]) - v.begin();
      v[idx] = box[i];
    }
  }

  cout << v.size();

  return 0;
}

/*
LIS 문제. 사실 N이 1000이라 그냥 O(N^2)인 DP로 풀면 되는데, LIS의 O(NlogN) 풀이를 사용했다. 12015 풀 때 썼던 이분탐색 방법 그대로 사용함.
문제 태그는 DP만 있길래 걍 DP로 분류해놨다.
*/