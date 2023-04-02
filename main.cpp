#include <iostream>
#define MAX 100000

using namespace std;

int N, S;
int num[MAX], sum[MAX] = {0};

bool check(int L);

int main(){
  scanf("%d %d", &N, &S);

  for(int i=0; i<N; i++)
    scanf("%d", &num[i]);
  
  sum[0] = num[0];
  for(int i=1; i<N; i++)
    sum[i] = sum[i-1] + num[i];

  int low = 1, high = N;
  int ans = 0;

  while(low <= high){
    int mid = (low + high)/2;

    if(check(mid)){
      ans = mid;
      high = mid-1;
    }
    else
      low = mid+1;
  }

  printf("%d", ans);

  return 0;
}

bool check(int L){
  if(sum[L-1] >= S) return true;

  for(int i=L; i<N; i++)
    if(sum[i] - sum[i-L] >= S) return true;
  
  return false;
}