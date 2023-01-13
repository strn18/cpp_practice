#include <iostream>
#include <algorithm>

using namespace std;

typedef struct{int d, h;}info;
info dragon[10000];

bool compare(info d1, info d2){
  return d1.d < d2.d;
}

int main(){
  int N;

  scanf("%d", &N);
  for(int i=0; i<N; i++)
    scanf("%d %d", &dragon[i].d, &dragon[i].h);

  sort(dragon, dragon+N, compare);

  for(int max_day=1; max_day<=N; max_day++){
    int count = 0, days = 0;
    for(int shoot=(N-max_day); shoot<N; shoot++){
      count += (dragon[shoot].d*days + dragon[shoot].h);
      days++;
    }
    printf("%d\n", count);
  }

  return 0;
}

/*
max_day가 N과 같을 때는, 모든 용을 한 번씩 잡는 것으로 생각하여, d가 가장 작은 용부터 가장 큰 용 순으로 잡는 방식으로 했다.
근데 이건 max_day != N일 때는 전혀 통하지 않네.. 가령 용1의 d가 1, h가 5000이고 용2가 1000, 0일 때, max_day가 1이면 용2가 아니라 용1을
잡아야 한다.
*/