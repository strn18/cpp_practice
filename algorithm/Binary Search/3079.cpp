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

/*
어렵지 않았던, 흔한 매개변수 탐색 문제. 최종적으로 걸리는 시간을 t초라고 두고, t초 동안 각 심사대에서 심사할 수 있는 사람의 수의 합이 
M 이상인지 아닌지 판별하는 문제로 바꾸면 된다. 해당 판별을 하는 부분은 check 함수에서 처리하고, 23행의 이진탐색 부분에서는 check 함수의 결과에
따라 start나 end값을 바꿔준다. 34행의 ans를 %d로 출력하는 바람에 한 번 틀림. 
*/