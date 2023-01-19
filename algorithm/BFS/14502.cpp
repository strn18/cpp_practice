#include <iostream>
#include <vector>
#include <queue>
#define MAX 8

using namespace std;

typedef struct{int r, c;} pos;

int N, M, count = -1;
int board[MAX][MAX];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
vector<pos> initial_empty, initial_virus, new_walls;

void choose_and_spread(int start, int depth);
int spread_virus(vector<pos> new_walls);

int main(){
  scanf("%d %d", &N, &M);

  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      scanf("%d", &board[i][j]);
      if(board[i][j] == 0)
        initial_empty.push_back({i, j});
      else if(board[i][j] == 2)
        initial_virus.push_back({i, j});
    }
  }

  choose_and_spread(0, 0);

  printf("%d", count);

  return 0;
}

void choose_and_spread(int start, int depth){
  if(depth == 3){
    count = max(count, spread_virus(new_walls));
  }
  else{
    for(int i=start; i<initial_empty.size(); i++){
      new_walls.push_back(initial_empty[i]);
      choose_and_spread(i+1, depth+1);
      new_walls.pop_back();
    }
  }
}

int spread_virus(vector<pos> new_walls){
  int count = 0;
  int cur_board[MAX][MAX];
  queue<pos> virus_q;
  
  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      cur_board[i][j] = board[i][j];

  for(int i=0; i<new_walls.size(); i++)
    cur_board[new_walls[i].r][new_walls[i].c] = 1;

  for(int i=0; i<initial_virus.size(); i++)
    virus_q.push({initial_virus[i].r, initial_virus[i].c});

  while(!virus_q.empty()){
    int cur_r = virus_q.front().r;
    int cur_c = virus_q.front().c;
    virus_q.pop();

    for(int i=0; i<4; i++){
      int next_r = cur_r + dr[i];
      int next_c = cur_c + dc[i];
      if(0<=next_r && next_r<N && 0<=next_c && next_c<M && cur_board[next_r][next_c] == 0){
        cur_board[next_r][next_c] = 2;
        virus_q.push({next_r, next_c});
      }
    }
  }

  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      if(cur_board[i][j] == 0)
        count++;
  
  return count;
}

/*
오랜만에 풀어본 bfs 문제. 문제 자체는 간단함. 모든 빈 칸 중에서 세 칸을 고르고, 고른 칸에 벽을 세운 다음 바이러스를 퍼뜨린다. 이후 안전 영역을 세서
count를 최댓값으로 갱신하면 된다. 세 칸을 고르는 것은 콤비네이션 방식으로 하면 되고, 바이러스를 퍼뜨리는 것은 세 칸에 벽을 세운 board에 대해서 
bfs를 쳐주면 된다.

어려운 문제는 아닌데, 빈 칸 중에서 세 칸을 고르는 방식을 좀 고민했다. 우선 빠른 탐색을 위해 빈 칸을 처음에 입력받을 때 애초에 벡터에 담아두기로
했는데, 이후 삼중 for문을 쓸까 하다가 코드가 더러워질 것 같아서 취소. 좀 고민하다가, 세 칸을 고르는 함수를 만들고 그 함수 안에서 바로 bfs를
돌려주기로 했다. choose_and_spread 함수는 빈 칸 중에서 칸을 고르고, 세 칸을 다 골랐으면 spread_virus 함수를 실행한다. spread_virus 함수는
인자로 받은 세 칸에 벽을 세운 다음, bfs를 돌려서 바이러스를 퍼뜨리고 안전 영역을 세서 count를 갱신한다.

이때 choose_and_spread 함수는, 빈 칸의 위치를 넣어둔 벡터인 initial_empty를 이용한다. 이 벡터의 start 인덱스부터 고르고, 골랐으니까 depth를
1 늘려서 다시 choose_and_spread를 실행해준다. depth가 3이 되었으면, 세 칸(new_walls 벡터에 있음)을 다 고른 거니까 spread_virus를 실행.

spread_virus 함수는, 우선 board를 복사받고, 고른 벽 세 개를 세운다음, virus_q에 초기 바이러스 위치를 넣는다. 그 다음, virus_q로 bfs 돌려주면
된다. 

좀 복잡해보일 순 있지만 별로 어려운 문제는 아님.
*/