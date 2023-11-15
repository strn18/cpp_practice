#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, ans = 0;
  vector<int> nums;

  cin >> N >> M;

  for(int i=0; i<N; i++){
    int num;
    cin >> num;
    nums.push_back(num);
  }

  sort(nums.begin(), nums.end());

  int s = 0, e = N-1;

  while(s < e){
    int sum = nums[s] + nums[e];

    if(sum == M){
      ans++;
      s++; e--;
    }
    else if(sum < M) s++;
    else e--;
  }

  cout << ans;

  return 0;
}

/*
걍 정렬 후 투 포인터 쓰면 되는데 해시(unordered_map) 쓴다고 나대다가 막혔던 문제. 
*/