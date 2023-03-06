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

/*
어렵지 않았던 매개변수 탐색 문제. 상한액을 limit로 잡았을 때, 각 지방 별로 사용하는 금액의 합이 총 예산(M) 이하인가? 를 따지는 결정 문제로
바꾸어서 풀면 된다. 이때 주의할 점은, limit의 최댓값을 구하는 것이므로, check 함수가 참일 때는 start에 mid+1을 넣어주는 방식이다.
그리고 초기 start 값을 M/N으로 잡은 이유는, 총 예산이 M이고, 지방은 N개이므로, 상한액을 M/N으로 잡으면 각 지방 별로 많이 써봤자 M/N밖에
쓰지 않게 되어, 각 지방 별 사용 금액 합이 반드시 M 이하가 된다. 그러므로 limit가 M/N보다 작아질 이유는 없다. 그래서 start 값을 그렇게 잡음.
그리고 22행에서 ans에 start를 먼저 넣어주었는데, 왜냐면 초기 start 값이 초기 end값(각 지방의 예산 요청(budget)의 최댓값)을 넘어버려서 24행의
while문을 바로 나올 수 있기 때문. 근데 이거 쓰면서 생각난건데, 이럴거면 애초에 end값을 다르게 설정하는 게 맞는 것 같기도 하네. 예를 들어
end에 max(M/N, max(budget)) 이런 식으로 해야했다.
*/