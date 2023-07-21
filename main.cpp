#include <iostream>
#include <vector>
#define MAX 8

using namespace std;

typedef struct{int num, rots, dir, r, c;} info;
vector<info> cctv;
const int max_rots[6] = {0, 4, 2, 4, 4, 1};

int N, M, ans = MAX*MAX;
int ori_board[MAX][MAX], cur_board[MAX][MAX];

int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};

void copy_board(void);
void rotate(int cur);
void mark_board(int cur);
void mark_dir(int r, int c, int d);
bool out_of_bound(int r, int c);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N >> M;

  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      cin >> ori_board[i][j];

      if(1 <= ori_board[i][j] && ori_board[i][j] <= 5)
        cctv.push_back({ori_board[i][j], max_rots[ori_board[i][j]], 0, i, j});
    }
  }

  rotate(cctv.size()-1);

  cout << ans;

  return 0;
}

void copy_board(void){
  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      cur_board[i][j] = ori_board[i][j];
}

void rotate(int cur){
  if(cur < 0){
    int count = 0;

    copy_board();

    for(int i=0; i<cctv.size(); i++)
      mark_board(i);
    
    for(int i=0; i<N; i++)
      for(int j=0; j<M; j++)
        if(cur_board[i][j] == 0) count++;
    
    ans = min(ans, count);
    return;
  }

  for(int i=0; i<cctv[cur].rots; i++){
    cctv[cur].dir = i;

    rotate(cur-1);
  }
}

void mark_board(int cur){
  int cur_r = cctv[cur].r;
  int cur_c = cctv[cur].c;
  int cur_d = cctv[cur].dir;

  if(cctv[cur].num == 1){
    mark_dir(cur_r, cur_c, cur_d);
  }
  else if(cctv[cur].num == 2){
    mark_dir(cur_r, cur_c, cur_d);
    mark_dir(cur_r, cur_c, cur_d+2);
  }
  else if(cctv[cur].num == 3){
    mark_dir(cur_r, cur_c, cur_d);
    mark_dir(cur_r, cur_c, (cur_d+1)%4);
  }
  else if(cctv[cur].num == 4){
    mark_dir(cur_r, cur_c, cur_d);
    mark_dir(cur_r, cur_c, (cur_d+1)%4);
    mark_dir(cur_r, cur_c, (cur_d+2)%4);
  }
  else{
    mark_dir(cur_r, cur_c, 0);
    mark_dir(cur_r, cur_c, 1);
    mark_dir(cur_r, cur_c, 2);
    mark_dir(cur_r, cur_c, 3);
  }
}

void mark_dir(int r, int c, int d){
  for(int i=1; true; i++){
    int nr = r + dr[d]*i;
    int nc = c + dc[d]*i;

    if(out_of_bound(nr, nc) || cur_board[nr][nc] == 6) break;
    if(cur_board[nr][nc] == 0) cur_board[nr][nc] = -1;
  }
}

bool out_of_bound(int r, int c){
  if(0<=r && r<N && 0<=c && c<M) return false;
  else return true;
}