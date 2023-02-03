#include <iostream>
#include <vector>
#define MAX 10000

using namespace std;

int main(){
  int N, n, max_total_time = 0;
  int time[MAX+1], total_time[MAX+1];
  vector<int> prev[MAX+1];

  scanf("%d", &N);
  for(int i=1; i<=N; i++){
    scanf("%d", &time[i]);
    scanf("%d", &n);
    for(int j=0; j<n; j++){
      int num;
      scanf("%d", &num);
      prev[i].push_back(num);
    }
  }

  for(int i=1; i<=N; i++){
    int max_prev = 0;

    for(int j=0; j<prev[i].size(); j++)
      max_prev = max(max_prev, total_time[prev[i][j]]);
    
    total_time[i] = max_prev + time[i];
    max_total_time = max(max_total_time, total_time[i]);
  }

  printf("%d", max_total_time);

  return 0;
}

/*
쉬웠던 dp문제. 위상정렬문제이기도 한데, 별로 복잡하지 않고 위상정렬을 굳이 할 필요가 없어보여서 그냥 dp로 풀었다.
total_time[i]: i번째 작업까지 끝내는 데 걸리는 시간. 이라고 두고, time[i]: i번째 작업 시간. 이라고 하면,
total_time[i] = max(i번째 작업의 선행 작업들의 total_time)+time[i]. 이라고 점화식을 세울 수 있다. 왜냐하면, i번째 작업을 하기 전에 그 작업의
선행 작업들을 모두 끝내야 하기에, 선행 작업들 중 가장 늦게 끝나는 작업이 끝난 후에 i번째 작업을 시작할 수 있기 때문임.

이걸 그냥 그대로 bottom-up으로 구현하고, max_total_time만 찾아서 마지막에 출력해주면 됨.
*/