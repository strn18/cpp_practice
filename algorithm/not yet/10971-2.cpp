/*
#include <iostream>

using namespace std;

int W[10][10];
int visit[10] = {0};
int N;
int current_cost = 0, lowest_cost = 10000001;

void Travel(int from, int to);

int main(){
  cin >> N;
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      cin >> W[i][j];

  Travel(0, 0);
  
  cout << lowest_cost;
  
  return 0;
}

void Travel(int from, int to){
  current_cost += W[from][to]; // 이번 도시로 올 때 드는 비용 더해주기
  visit[to] = 1;

  int visit_over = 1;
  for(int i=0; i<N; i++)
    if(!visit[i]){ // 하나라도 방문 안 했다면, visit_over은 false
      visit_over = 0;
      break;
    }

  if(visit_over){ // 모든 도시 방문했을 때
    if(W[to][0]){ // 첫 도시로 돌아갈 수 있다면 최소 비용 갱신
      current_cost += W[to][0];
      lowest_cost = min(lowest_cost, current_cost);
      current_cost -= W[to][0];
    }
  }
  else{ // 아직 방문 안 끝났다면 다음 도시 마저 방문
    for(int i=0; i<N; i++)
      if(!visit[i] && W[to][i])
        Travel(to, i);
  }

  current_cost -= W[from][to]; // 이번 도시로 오는 계산은 끝이니까 비용 빼주기
  visit[to] = 0;
}
다시 풀어본 외판원 순회 문제. 원래 풀이와 방식은 거의 같았지만 좀 더 깔끔해졌다. 근데 하나 간과했던 부분이 있었음. 이번 풀이에서는 순회를 시작하는 첫 도시를 i=[0, N) 범위로 for문을 돌리면서 Travel(i, i) 이렇게 반복해줬는데, 사실 그럴 필요가 없는게 도시 0에서 시작해서 다시 0으로 돌아오나, 1에서 시작해서 1로 돌아오나 그 루트만 같다면 어차피 결과값은 똑같아짐. 즉 이번 풀이 방식대로 하면 쓸데없이 N번 더 계산하게 되었던 것임. 그래서인지 백준 계산 시간이 10배 이상 늘어났다. 그 부분 수정하고 다시 제출한 결과 계산 시간 동일해짐을 확인했음. 그 부분 제외하면 코드가 크게 다른 부분은 없었다.
*/