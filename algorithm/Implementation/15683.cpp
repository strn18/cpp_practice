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

/*
어렵진 않으나 매우 매우 귀찮은 구현 문제.

처음엔 좀 막막했는데 단계 별로 잘 나눠보니 할만했음.

일단, cctv를 회전하는 모든 경우의 수를 구해야 한다. 즉, cctv가 3개 있는데 종류는 다 1번이라고 하자. 이때, 방향(우 하 좌 상)을 0~3이라고 가정하면,
cctv 3개의 방향이 000 001 002 003 010 011 012 013 020 ... 333 의 경우를 모두 구하고, 각 경우마다 생기는 사각지대의 개수를 다 구하보면 된다.

이를 위해, 우선 cctv의 정보를 담는 info라는 구조체를 선언함. {int num, rots, dir, r, c;} 에서, r와 c는 그 cctv의 위치이고, num은 그 cctv의 
종류(1~5번), rots는 그 종류가 가지는 방향 가짓수(1번이면 4, 2번이면 2, ...), dir은 그 cctv의 현재 방향이다. dir 값은 0 ~ rots-1 의 값을 가질 수
있음. 31행에서 board 값 받을 때, 그 값이 1~5라면 cctv이므로 그때 vector인 cctv에 값을 push_back 해준다. 이때, num, r, c는 그냥 그대로 값을 받으면
되고, dir은 우선 0으로 대충 초기화해놓음. 그러면 rots는 어떡하느냐? 9행에서 max_rots에 미리 값(방향 가짓수)을 넣어놨다. 그 값을 그대로 넣었음.

그 다음은 모든 회전 경우의 수를 구할 rotate 함수이다. 얘는 int cur를 인수로 받도록 했는데, 작동 방식은 다음과 같음.
1) cur번째 cctv를 한 크리크 회전시킨다.
2) rotate(cur-1)을 실행하여, 그 앞 cctv들이 회전하는 모든 경우의 수를 구함.
이를 반복하여, cur번째 cctv를 다 회전시킨다. 

뭔 소리나면, 종류가 1번인 cctv가 3개 있다고 하자. 각각 cctv[0]~cctv[2]라고 하겠음. 이때 rotate(2)를 실행한다면? 세 cctv의 방향값이 각각
000 100 200 300 010 110 210 310 ... 333 인 경우가 모두 구해지게 된다. 자세한 건 68행을 보면 알 수 있음.

만약 cur == -1이라면? 재귀를 종료해야 함. 52행에서, 이제 0번째 cctv까지 회전이 끝났으니깐, 현재 각 cctv의 정보(방향값)를 토대로, 사각지대의 
개수를 구해준다. 우선 copy_board로 원본 ori_board 값을 cur_board에 복사해준다. 그 다음 각 cctv에 대해서 mark_board를 호출하여, 각 cctv가 
비추는 곳의 cur_board 값을 -1로 바꿔준다. 그 다음, 사각지대(cur_board 값이 0)의 개수를 세어 ans를 갱신하면 됨. 

mark_board(int cur)는 cur번째 cctv가 비추는 곳을 모두 찾아 cur_board 값을 -1로 바꾼다. 이를 위해, 그냥 cctv의 종류(1~5번) 별로 if문을 나눠서,
가리키는 방향(d)만 / d와 d의 반대 방향(d+2) / d와 d의 옆 방향(d+1) / d와 d+1과 d+2 / 모든 방향
에 대해서, mark_dir을 호출하였다. 이때, d+1이나 d+2가 3(방향값을 0~3으로 표현한댔으니까)을 넘어갈 수 있으므로 4로 나머지 연산을 하는 것에 유의. 

mark_dir(int r, int c, int d)은 (r, c)에서 시작해서, d라는 방향으로 cctv를 쭉 비췄을 때, 비추는 곳의 cur_board 값을 -1로 바꿔준다.
이거는 그냥 간단한데, 해당 방향으로 한칸 한칸 전진하면서, 해당 칸의 cur_board 값이 0이라면 -1로 바꿔준다. 그러다가 벽 or 범위 밖을 만나면 break.
*/