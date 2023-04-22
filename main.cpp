#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, count = 0;
  int nums[10] = {0};

  cin >> N;

  while(N>0){
    nums[N%10]++;
    N/=10;
  }

  for(int i=0; i<10; i++){
    if(i==6 || i==9) continue;
    count = max(count, nums[i]);
  }

  if(nums[6] == nums[9]) count = max(count, nums[6]);
  else if(nums[6] > nums[9]) count = max(count, nums[9] + (nums[6]-nums[9]+1)/2);
  else count = max(count, nums[6] + (nums[9]-nums[6]+1)/2);

  cout << count;

  return 0;
}