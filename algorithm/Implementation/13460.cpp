#include <iostream>
#include <string>
#define MAX 10

using namespace std;

typedef struct {int r, c;} pos;

int N, M, ans = 11;
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};

void copy_board(string from[MAX], string to[MAX]);
void move(int dir, string board[MAX], pos red, pos blue, int count);
pos move_bead(int dir, string board[MAX], pos bead);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string board[MAX];
  pos red, blue;

  cin >> N >> M;

  for(int i=0; i<N; i++)
    cin >> board[i];
  
  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      if(board[i][j] == 'R') red = {i, j};
      else if(board[i][j] == 'B') blue = {i, j};
    }
  }
  
  for(int i=0; i<4; i++)
    move(i, board, red, blue, 1);
  
  cout << (ans == 11 ? -1 : ans);

  return 0;
}

void copy_board(string from[MAX], string to[MAX]){
  for(int i=0; i<N; i++)
    to[i] = from[i];
}

void move(int dir, string board[MAX], pos red, pos blue, int count){
  bool red_first = true;
  string next[MAX];

  copy_board(board, next);

  if(dir == 0 && blue.r < red.r) red_first = false;
  else if(dir == 1 && blue.c < red.c) red_first = false;
  else if(dir == 2 && red.r < blue.r) red_first = false;
  else if(dir == 3 && red.c < blue.c) red_first = false;

  if(red_first){
    red = move_bead(dir, next, red);
    blue = move_bead(dir, next, blue);
  }
  else{
    blue = move_bead(dir, next, blue);
    red = move_bead(dir, next, red);
  }

  if(next[blue.r][blue.c] == 'O') return;

  if(next[red.r][red.c] == 'O'){
    ans = min(ans, count);
    return;
  }

  if(count == 10) return;

  for(int i=0; i<4; i++){
    if(i == dir || (i+2)%4 == dir) continue;
    move(i, next, red, blue, count+1);
  }
}

pos move_bead(int dir, string board[MAX], pos bead){
  while(true){
    int nr = bead.r+dr[dir];
    int nc = bead.c+dc[dir];

    if(board[nr][nc] == '.'){
      board[nr][nc] = board[bead.r][bead.c];
      board[bead.r][bead.c] = '.';
      bead = {nr, nc};
    }
    else if(board[nr][nc] == 'O'){
      board[bead.r][bead.c] = '.';
      return {nr, nc};
    }
    else return bead;
  }
}

/*
백준 태그에는 없긴 한데 bfs 말고 dfs로도 풀이가 가능한 구현 문제. 어렵진 않은데 구현이 귀찮음.

move 함수는 보드를 기울이는 함수이다. move_bead 함수는 구슬을 움직이는(보드를 기울였을 때 어느 칸으로 가는지 리턴함) 함수이다.

move 함수는, 우선 상하좌우 별로 어느 구슬이 먼저 움직이는지 파악함. 즉, 보드를 상 으로 기울인다고 하면, 파랑 구슬의 r 값이 더 작을 경우
파랑 구슬이 먼저 움직이도록 한다(같은 열에 있을 경우, 파랑이 더 위에 있으면 더 먼저 움직여야하니깐). 그렇지 않으면 빨강 구슬이 먼저 움직임.
이걸 담당하는게 55~58행.

이를 통해 빨강 구슬이 먼저 움직여도 되는지(red_first가 참) 체크하고, 그 순서대로 빨강 파랑 구슬을 움직인다(60~67행).

move_bead 함수는 어떠한 구슬(bead로 위치값이 주어짐)을 dir 방향으로 움직일 때, 최종적으로 도달하는 위치값을 리턴한다. 이를 위해 dr과 dc를
만들어서 4방향으로 한 칸씩 알아보도록 했고, 만약 지금 알아보는 칸(움직일 칸)이 빈 칸이면(89행) board 값 바꿔주고 구슬 위치도 변경. 
만약 구멍이면(94행) 구슬이 원래 있던 값을 빈 칸으로 만들어놓고, 그 구멍 위치를 리턴(구슬이 거기로 빠지게 되니까). 그렇지 않다면(벽 또는
다른 구슬이 있다면. 98행), 구슬은 더 이상 안 움직이니깐 원래 있던 구슬 위치 값을 리턴한다.

이렇게 하면 move 함수에서 68행까지 했을 때, red에는 판을 기울였을 때 빨강 구슬의 위치, blue에는 파랑 구슬의 위치값이 들어가있음. 이때,
blue의 위치가 구멍 칸이라면 파랑 구슬이 구멍에 빠진 거니까 더 이상 진행 필요 x, 걍 리턴한다. 만약 그렇지 않고 빨강 구슬이 구멍에 빠졌다면
지금까지 기울인 횟수 count로 ans를 갱신하고 리턴. 만약 그렇지 않고 지금까지 10번 기울였다면 이제 끝이니까 걍 리턴. 다 아니라면, 78행에서
다음 기울이기 ㄱㄱ. 
근데, 만약 방금 상 방향으로 기울였다면, 또다시 상 방향으로 기울이거나 하 방향으로 기울일 필요 없다. 왜냐? 상 방향은 일단 이미 기울인 거니까
당연히 아님. 하 방향도 볼 필요 없는데, "상 -> 하" 이렇게 기울일 바엔 그냥 "하" 한 번만 기울여도 됨. 구슬을 위로 보냈다 아래로 보내나, 
그냥 아래로 보내나 결과는 같으니까. 그러므로 하 방향도 볼 필요 없다(최소 기울임 횟수가 아니므로). 이를 79행에서 걸러줬는데, 4방향을 원래는 
0 1 2 3 -> 상 하 좌 우 이렇게 많이 했었는데, 상 좌 하 우 이렇게 했다. 이러면 방금 기울인 방향 인덱스+2 를 해주고 4로 나머지 연산을 해주면
반대 방향을 구할 수 있음. 가령, 하 방향은 2인데, 거기에 2 더하면 4이고, 4로 나머지 연산 하면 0임. 0은 어느 방향? 상 방향. 하 방향과 반대이다.
이 방식으로 79행에서 방금 기울인 방향 or 그 반대 방향은 걸러주고, 나머지 두 방향으로 dfs 치면 끝.
*/