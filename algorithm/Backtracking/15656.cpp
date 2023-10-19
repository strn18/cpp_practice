#include <iostream>
#include <algorithm>
#define MAX 7

using namespace std;

int N, M;
int nums[MAX], choice[MAX];

void choose(int idx);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N >> M;

  for(int i=0; i<N; i++)
    cin >> nums[i];
  
  sort(nums, nums + N);
  
  choose(0);

  return 0;
}

void choose(int idx){
  if(idx == M){
    for(int i=0; i<M; i++)
      cout << choice[i] << ' ';
    cout << '\n';
    return;
  }

  for(int i=0; i<N; i++){
    choice[idx] = nums[i];
    choose(idx + 1);
  }
}