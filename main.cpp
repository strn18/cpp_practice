#include <iostream>

using namespace std;

int N, k;

long long count_less_than(int n);

int main(){
  int start, end;
  long long ans;

  scanf("%d %d", &N, &k);

  start = 1, end = k; // B[k] <= k
  
  while(start <= end){
    int mid = (start+end)/2;

    if(count_less_than(mid) < k){
      ans = mid;
      start = mid+1;
    }
    else
      end = mid-1;
  }

  printf("%d", ans);

  return 0;
}

long long count_less_than(int n){
  long long count = 0;

  for(int i=1; i<=N; i++)
    count += min(N, (n-1)/i);

  return count;
}