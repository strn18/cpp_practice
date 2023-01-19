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