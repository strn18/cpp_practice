#include <iostream>
#include <queue>
#define MAX 50
#define INF 2500

using namespace std;

int board[MAX][MAX];
int cost[MAX][MAX];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void dijkstra(int N);

int main(){
  int n;

  scanf("%d", &n);

  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      scanf("%1d", &board[i][j]);
      cost[i][j] = INF;
    }
  }
  cost[0][0] = 0;

  dijkstra(n);

  printf("%d", cost[n-1][n-1]);

  return 0;
}

void dijkstra(int N){
  priority_queue<pair<int, pair<int, int>>> pq; // (-비용, (행, 열))
  pq.push({0, {0, 0}});

  while(!pq.empty()){
    int cur_cost = -pq.top().first;
    int cur_r = pq.top().second.first;
    int cur_c = pq.top().second.second;
    pq.pop();

    if(cur_cost > cost[cur_r][cur_c]) continue;

    for(int i=0; i<4; i++){
      int next_r = cur_r + dr[i];
      int next_c = cur_c + dc[i];

      if(0<=next_r && next_r<N && 0<=next_c && next_c<N){
        int next_cost = board[next_r][next_c] ? 0 : 1;

        if(cur_cost + next_cost < cost[next_r][next_c]){
          cost[next_r][next_c] = cur_cost + next_cost;
          pq.push({-cost[next_r][next_c], {next_r, next_c}});
        }
      }
    }
  }
}