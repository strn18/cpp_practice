#include <iostream>
#define MAX 10000

using namespace std;

int K, N;
long long lan[MAX];

bool check(long long length);

int main(){
  long long start = 1, end = 0, ans = 0;

  scanf("%d %d", &K, &N);

  for(int i=0; i<K; i++){
    scanf("%lld", &lan[i]);
    end = max(end, lan[i]);
  }

  while(start <= end){
    long long mid = (start+end)/2;

    if(check(mid)){
      ans = mid;
      start = mid+1;
    }
    else
      end = mid-1;
  }

  printf("%lld", ans);
  
  return 0;
}

bool check(long long length){
  long long count = 0;

  for(int i=0; i<K; i++)
    count += lan[i]/length;
  
  return (count >= N) ? true : false;
}