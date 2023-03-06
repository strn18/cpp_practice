#include <iostream>
#define MAX 10000

using namespace std;

int N, M;
int budget[MAX];

bool check(int limit);

int main(){
  int ans, start, end = 0;

  scanf("%d", &N);
  for(int i=0; i<N; i++){
    scanf("%d", &budget[i]);
    end = max(end, budget[i]);
  }
  scanf("%d", &M);

  start = M/N;
  ans = start;

  while(start <= end){
    int mid = (start+end)/2;

    if(check(mid)){
      ans = mid;
      start = mid+1;
    }
    else
      end = mid-1;
  }

  printf("%d", ans);

  return 0;
}

bool check(int limit){
  int count = 0;

  for(int i=0; i<N; i++)
    count += min(budget[i], limit);
  
  return (count <= M ? true : false);
}