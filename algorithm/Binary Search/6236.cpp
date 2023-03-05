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

/*
2343이랑 거의 똑같은 문제. 다만, 2343에서는 이진탐색 범위를 sum(lec)/M ~ sum(lec)로 잡았었는데, 여기서는 max(spend) ~ sum(spend)로 잡았다.
사실 이게 맞음. 하루에 쓰는 금액인 spend 중, 최댓값 보다는 k(인출금액)가 반드시 커야한다. 그러므로 최솟값은 max(spend)가 된다.
*/