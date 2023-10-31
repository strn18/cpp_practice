#include <iostream>
#include <vector>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, K, count = 0;
  vector<pair<int, bool>> nums;

  cin >> N >> K;

  for(int i=2; i<=N; i++)
    nums.push_back({i, true});
  
  for(int i=0; i<N-1; i++){
    for(int j=i; j<N-1; j++){
      if(nums[j].second && (nums[j].first % nums[i].first == 0)){
        nums[j].second = false;
        if(++count == K){
          cout << nums[j].first;
          return 0;
        }
      }
    }
  }

  return 0;
}