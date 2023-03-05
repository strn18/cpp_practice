#include <iostream>
#define MAX 100000
#define INF 2100000000

using namespace std;

int N, M;
int time[MAX];

bool check(long long t);

int main(){
  long long start = INF, end, ans;

  scanf("%d %d", &N, &M);
  for(int i=0; i<N; i++){
    scanf("%d", &time[i]);
    start = min(start, (long long)time[i]);
  }
  end = start*M;
  ans = end;

  while(start <= end){
    long long mid = (start+end)/2;

    if(check(mid)){
      ans = mid;
      end = mid-1;
    }
    else
      start = mid+1;
  }

  printf("%lld", ans);

  return 0;
}

bool check(long long t){
  long long count = 0;

  for(int i=0; i<N; i++)
    count += t/time[i];
  
  return (count >= M ? true : false);
}