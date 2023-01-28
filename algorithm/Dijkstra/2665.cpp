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

/*
어렵지 않았던 다익스트라 문제. 처음에는 bfs로 풀면 되지 않나? 싶어서 bfs로 생각을 좀 해봤다. 

주어진 값을 담은 board 배열과, 그 칸까지 가기 위해 색을 바꿔야하는 방의 최소 개수를 나타내는 change 배열을 만든다. 이때 초기값은 2500으로 한다.
그 후 첫 칸부터 인접칸으로 bfs를 치는데, 인접칸이 흰 방이면 인접칸보다 이번 칸의 change 값이 작을 때 그걸로 바꿔주고 인접칸을 큐에 넣으면서 bfs로
확산한다. 인접칸이 검은 방이면 이번 칸의 change 값+1이 인접칸의 change 값보다 작으면 그걸로 바꿔주고 인접칸을 큐에 넣으면서 bfs로 확산한다.
대충 이렇게 짜봤는데, 돌아가긴 할 것 같은데 쓸데없이 중복해서 계산하는 경우도 좀 있을 것 같고 해서, 다익스트라로 바꿨다. 다익스트라로 바꿔도 되지
않을까? 싶은 생각이 든 시점은, change의 초기값을 2500으로 두고, 이번 칸의 change 값(인접이 검정이면 +1)과 인접칸의 change 값을 비교하여 전자가
더 작으면 값을 바꿔주고 하는게 다익스트라랑 거의 유사했기 때문.

그래서 다익스트라로 바꿨다. 딱히 복잡한 부분은 없었고, 행 열을 넣기 위해 pair 쓰고, 간선 대신에 인접 4방향 보고, next_cost를 1 or 0으로 넣어주는
것만 신경쓰면 됐음. 처음에 MAX를 20으로 하는 바람에 한 번 틀렸는데, 바꾸고 제출하니 맞았다.
*/