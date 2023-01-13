#include <iostream>
#include <algorithm>

using namespace std;

int N, M;
int nums[8], choices[8];
bool choosed[8] = {false};

void choose(int n); // n번째 선택(0-base)

int main(){
  scanf("%d %d", &N, &M);
  for(int i=0; i<N; i++)
    scanf("%d", &nums[i]);
  sort(nums, nums+N);
  
  choose(0);

  return 0;
}

void choose(int n){
  for(int i=0; i<N; i++){
    if(!choosed[i]){
      choosed[i] = true;
      choices[n] = nums[i];
      if(n==M-1){
        for(int j=0; j<M; j++)
          printf("%d ", choices[j]);
        printf("\n");
      }
      else{
        choose(n+1);
      }
      choosed[i] = false;
      choices[n] = 0;
    }
  }
}

/*
N개의 수를 받아 오름차순 정렬 하는 것 제외하면 다른 N과 M 문제들과 똑같은 문제
*/