/*
#include <iostream>

using namespace std;

int W[10][10];
int visit[10] = {0};
int N;
int cost = 0;
int min_cost = 10000001;

void trav(int prev, int cur);

int main(){
  cin >> N;

  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      cin >> W[i][j];

  trav(0, 0);

  cout << min_cost;

  return 0;
}

void trav(int prev, int cur){
  int end = 1; // 이번 방문으로 모든 노드 방문이 끝났는지 여부
  
  if(visit[cur]) // 이미 방문한 노드라면 돌아가기
    return;
  
  visit[cur] = 1; // 방문하지 않았다면 체크하고 여기까지의 비용 갱신
  cost += W[prev][cur];

  for(int i=0; i<N; i++){
    if(visit[i] != 1){ // 아직 방문 안 한 노드가 있는지 확인
      end = 0;
      break;
    }
  }
  if(end){ // 1. 모든 노드를 방문한 경우
    if(W[cur][0]){ // 이번 노드에서 처음 노드로 돌아갈 수 있다면(순회 가능)
      cost += W[cur][0]; // 처음 노드로 돌아가는 비용 더해주고
      min_cost = min(min_cost, cost); // 최소 비용 갱신
      cost -= W[cur][0]; // 갱신 후 백트래킹을 위해 다시 빼준다
    }
    cost -= W[prev][cur]; // 이번 노드로 오는 비용 빼주고
    visit[cur] = 0; // 이번 노드 방문 표시 지우고 백트래킹
    return;
  }

  for(int i=0; i<N; i++) // 2. 아직 모든 노드 방문 안 한 경우
    if(W[cur][i]) // 방문할 수 있는 노드를 방문
      trav(cur, i);
  cost -= W[prev][cur]; // 끝났으면 이번 노드로 오는 비용 빼주고
  visit[cur] = 0; // 이번 노드 방문 표시 지우고 백트래킹
}

*/