#include <iostream>
#include <queue>
#define MAX 20

using namespace std;

typedef struct{int r, c;} pos;

int N;
int board[MAX][MAX];

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

pos fish; // 먹을 물고기 위치
int fish_time; // 그 물고기 먹으러 이동하는 시간

void bfs(int r, int c, int h); // (r, c)에 있는 크기 h의 상어가 먹을 물고기 찾기(fish와 fish_time을 갱신)

int main(){
  pos shark; // 상어 위치
  int shark_h, ate, count; // 상어 크기, 먹은 물고기 수, 총 시간

  scanf("%d", &N);

  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      scanf("%d", &board[i][j]);
      if(board[i][j] == 9)
        shark = {i, j};
    }
  }

  shark_h = 2; ate = 0; count = 0;
  while(1){
    fish = {MAX, MAX}; // 물고기 위치와 시간 초기화
    fish_time = 0;

    bfs(shark.r, shark.c, shark_h);

    if(!fish_time) break; // 시간이 그대로라면(=먹을 물고기를 못 찾았다면) 끝임

    board[shark.r][shark.c] = 0; // 상어가 원래 있던 위치는 빈 칸으로
    shark = fish; // 상어를 먹을 물고기 위치로 옮김
    board[shark.r][shark.c] = 9; // 상어 표시
    if(++ate == shark_h){ // 크기 만큼의 물고기를 먹었으면 상어 크기 커짐
      shark_h++;
      ate = 0;
    }

    count += fish_time; // 이동 시간 더해주기
  }

  printf("%d", count);

  return 0;
}

void bfs(int r, int c, int h){
  int time_count = 0;
  bool visited[MAX][MAX] = {false};
  queue<pos> Q;

  visited[r][c] = true;
  Q.push({r, c});
  while(!Q.empty() && !fish_time){ // 큐가 안 비었고, 먹을 물고기를 못 찾았다면 반복
    time_count++;
    int q_size = Q.size(); // 현재 큐에 들어있는 위치값만 봐야함. 밑에서 큐에 더 추가되는 값들은 지금 기준으로 1초 후의 위치값들이기 때문.

    for(int q=0; q<q_size; q++){
      pos cur = Q.front();
      Q.pop();

      for(int i=0; i<4; i++){
        int nr = cur.r + dr[i];
        int nc = cur.c + dc[i];
        if(0<=nr && nr<N && 0<=nc && nc<N && !visited[nr][nc] && board[nr][nc]<=h){ // 인접칸이 범위 안이고, 방문 안 했고, 지나갈 수 있을 때
          if(board[nr][nc] == 0 || board[nr][nc] == h){ // 빈 칸이거나 먹을 수 없는 물고기라면, 1초 후에 갈 위치니까 큐에 넣어준다.
            visited[nr][nc] = true;
            Q.push({nr, nc});
          }
          else{ // 먹을 수 있는 물고기 발견 -> fish와 fish_time 갱신. fish_time이 갱신되니까 위의 while문을 더 돌 필요 없음.
            if((nr < fish.r) || (nr == fish.r && nc < fish.c))
              fish = {nr, nc};
            fish_time = time_count;
          }
        }
      }
    }
  }
}

/*
복잡했지만 그리 어렵지는 않았던 bfs 문제. 상어의 위치로부터 bfs를 시작하여, 먹을 수 있는 물고기 칸을 찾았다면 그 물고기를 상어가 먹고, 다시
그 위치에 대해서 bfs를 돌리고...를 반복하면 된다. 이때 먹을 수 있는 물고기 칸이 같은 거리에 여러 개 있다면, 가장 위에, 그것도 같다면 가장
왼쪽에 있는 물고기를 먹는다. 그리고 물고기를 먹는데 걸리는 시간(=거리)을 계속 더해가면서, 더 이상 먹을 수 있는 물고기가 없을 때 break하여
그걸 출력해주면 된다.

코드가 좀 복잡하긴 하지만 딱히 어려운 부분은 없었고, bfs 함수만 잘 구현하면 됐다. 자세한 건 주석에 써놓음
*/