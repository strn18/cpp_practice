#include <iostream>
#include <algorithm>
#define MAX 200000

using namespace std;

int N, C;
int house[MAX];

bool check(int d);

int main(){
  int ans = 0;
  
  scanf("%d %d", &N, &C);
  for(int i=0; i<N; i++)
    scanf("%d", &house[i]);
  
  sort(house, house+N);

  int start = 1, end = (house[N-1]-house[0]) / (C-1);
  while(start<=end){
    int mid = (start+end)/2;

    if(check(mid)){
      ans = max(ans, mid);
      start = mid+1;
    }
    else
      end = mid-1;
  }

  printf("%d", ans);
  
  return 0;
}

bool check(int d){
  int prev_house_idx = 0;

  for(int i=1; i<C; i++){
    bool flag = false;
    
    for(int j=prev_house_idx+1; j<N; j++){
      if(house[j]-house[prev_house_idx] >= d){
        prev_house_idx = j;
        flag = true;
        break;
      }
    }

    if(!flag) return false;
  }

  return true;
}