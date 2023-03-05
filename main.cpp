#include <iostream>
#define MAX 100000

using namespace std;

int N, M;
int spend[MAX];

bool check(int k);

int main(){
  int ans, start = 0, end = 0;

  scanf("%d %d", &N, &M);
  for(int i=0; i<N; i++){
    scanf("%d", &spend[i]);
    start = max(start, spend[i]);
    end += spend[i];
  }

  while(start <= end){
    int mid = (start+end)/2;

    if(check(mid)){
      ans = mid;
      end = mid-1;
    }
    else
      start = mid+1;
  }

  printf("%d", ans);

  return 0;
}

bool check(int k){
  int count = 1, money = k;

  for(int i=0; i<N; i++){
    if(spend[i] > money){
      count++;
      money = k-spend[i];
    }
    else
      money -= spend[i];
  }

  return (count <= M ? true : false);
}