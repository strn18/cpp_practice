#include <iostream>
#include <queue>
#include <vector>
#define INF 99999
#define MAX 100

using namespace std;

int main(){
  int N, M;
  int board[MAX][MAX], dist[MAX][MAX];
  int dr[4] = {-1, 1, 0, 0};
  int dc[4] = {0, 0, -1, 1};

  scanf("%d %d", &M, &N);

  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      scanf("%1d" ,&board[i][j]);
      dist[i][j] = INF;
    }
  }
  dist[0][0] = 0;

  priority_queue<pair<int, pair<int, int>>> pq; // (비용, (행, 열))
  pq.push({0, make_pair(0, 0)});

  while(!pq.empty()){
    int cur_cost = -pq.top().first;
    int cur_r = pq.top().second.first;
    int cur_c = pq.top().second.second;
    pq.pop();

    if(cur_r == N-1 && cur_c == M-1) break;
    if(cur_cost > dist[cur_r][cur_c]) continue;

    for(int i=0; i<4; i++){
      int next_r = cur_r + dr[i];
      int next_c = cur_c + dc[i];

      if(next_r<0 || N<=next_r || next_c<0 || M<=next_c) continue;

      int next_cost = board[next_r][next_c];
      if(cur_cost + next_cost < dist[next_r][next_c]){
        dist[next_r][next_c] = cur_cost + next_cost;
        pq.push({-dist[next_r][next_c], make_pair(next_r, next_c)});
      }
    }
  }

  printf("%d", dist[N-1][M-1]);

  return 0;
}