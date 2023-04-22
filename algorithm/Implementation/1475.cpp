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

/*
쉬웠던 구현 문제. https://blockdmask.tistory.com/97 여기 풀이를 보니까, 내가 한 것처럼 24~26행에서 경우를 나눌 필요 없이 그냥 6과 9의 개수에
1을 더한 후(합이 홀수 일 경우를 위해), 반으로 나눠준 값을 사용하면 된다.
*/