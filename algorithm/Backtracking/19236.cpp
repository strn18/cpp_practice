#include <iostream>
#include <algorithm>

using namespace std;

int result = 0, maximum = 0;
int dr[9] = {-999, -1, -1, 0, 1, 1, 1, 0, -1};
int dc[9] = {-999, 0, -1, -1, -1, 0, 1, 1, 1};
typedef struct{int n, d;}info; // n: 번호, d: 방향. 상어 n은 0, 빈 칸 n은 -1
info board[4][4];

void fish_move(info board[][4], int r, int c); // (r, c)의 물고기를 이동시킨다.
bool shark_move_able(info board[][4], int r, int c, int mv); // (r, c)의 상어가 자기 방향으로 mv칸 이동할 수 있다면 true, 없다면 false
int shark_move(info board[][4], int r, int c, int mv); // (r, c)의 상어를 자기 방향으로 mv칸 이동시킨다.
void update(info board[][4]); // board의 물고기들을 이동시키고, 상어를 이동한다.

int main(){
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      scanf("%d %d", &board[i][j].n, &board[i][j].d);

  result += board[0][0].n; // 처음에 먹은 물고기 번호
  board[0][0].n = 0; // 상어 배치
  update(board);

  printf("%d", maximum);

  return 0;
}

void fish_move(info board[][4], int r, int c){
  for(1; board[r][c].d<=8; board[r][c].d++){ // 현재 d부터 8까지 d를 증가시키며 물고기를 회전한다.
    int mr = r+dr[board[r][c].d]; // 물고기가 이동할 칸의 r좌표
    int mc = c+dc[board[r][c].d]; // 물고기가 이동할 칸의 c좌표
    if(0<=mr && mr<4 && 0<=mc && mc<4){ // 범위 안이면서
      if(board[mr][mc].n != 0){ // 해당 칸에 상어가 없다면 이동해줌
        info temp = board[r][c];
        board[r][c] = board[mr][mc];
        board[mr][mc] = temp;
        return;
      }
    }
  }
  // 8까지 회전했는데 이동할 칸이 없었다면, 1부터 시작해서 다시 회전하며 이동할 칸을 찾는다.
  for(board[r][c].d=1; board[r][c].d<=8; board[r][c].d++){
    int mr = r+dr[board[r][c].d];
    int mc = c+dc[board[r][c].d];
    if(0<=mr && mr<4 && 0<=mc && mc<4){
      if(board[mr][mc].n != 0){
        info temp = board[r][c];
        board[r][c] = board[mr][mc];
        board[mr][mc] = temp;
        return;
      }
    }
  }
}

bool shark_move_able(info board[][4], int r, int c, int mv){
  int mr = r+(dr[board[r][c].d]*mv); // 상어가 이동할 칸의 r좌표
  int mc = c+(dc[board[r][c].d]*mv); // 상어가 이동할 칸의 c좌표
  if(0<=mr && mr<4 && 0<=mc && mc<4) // 범위 안이면서
    if(board[mr][mc].n != -1) // 해당 칸이 빈 칸이 아니라면(물고기가 있다면)
      return true;
  return false;
}

int shark_move(info board[][4], int r, int c, int mv){
  int mr = r+(dr[board[r][c].d]*mv);
  int mc = c+(dc[board[r][c].d]*mv);
  int num = board[mr][mc].n; // 상어가 이동할 칸의 물고기 번호
  board[mr][mc].n = 0;
  board[r][c].n = -1;
  return num; // 먹은 물고기 번호 리턴해주기
}

void update(info board[][4]){
  // fish move
  for(int i=1; i<=16; i++){ // 1~16번 물고기 차례로 이동시키기
    bool moved = false;
    for(int r=0; r<4 && !moved; r++){ // 이번 물고기가 이미 이동했다면 더 이상 볼 필요 없음. 다음 물고기로 넘어가기
      for(int c=0; c<4 && !moved; c++){
        if(board[r][c].n == i){ // i번 물고기 발견
          fish_move(board, r, c);
          moved = true;
        }
      }
    }
  }

  // shark move
  for(int r=0; r<4; r++){
    for(int c=0; c<4; c++){
      if(board[r][c].n == 0){ // 상어 발견
        int eat = 0; // 상어가 이번에 이동할 때 먹은 물고기 번호
        for(int mv=1; mv<=3; mv++){ // 4*4 판이므로 1~3칸 이동 가능
          if(shark_move_able(board, r, c, mv)){
            info new_board[4][4]; // 인자로 넘겨줄 복제 판 생성
            copy(&board[0][0], &board[0][0]+16, &new_board[0][0]);
            eat = shark_move(new_board, r, c, mv); // 상어를 이동시키며, 먹은 물고기 번호 기록
            result += eat; // 합계에 더해줌
            update(new_board); // mv칸 이동한 상태에서, 다음 분기로 dfs
            result -= eat; // mv칸 이동한 상태에서 나오는 경우를 모두 찾았다면, 아까 더해준 번호를 다시 빼주며 backtracking
          }
        }
        if(!eat) // 만약 1~3칸 모두 이동 못 한다면 지금까지 먹은 물고기 번호 합계로 최댓값 갱신
          maximum = max(maximum, result);
      }
    }
  }
}

/*
말도 안 되는 실수 때문에 쓸데없이 오래걸렸던 백트래킹 문제. 풀이 떠올리는 거랑 코드 짜는 건 딱히 오래 걸리지 않았는데, 다 짜놓고 딱 두 가지 별 거
아닌 부분 때문에 틀린 답이 떠서 시간을 많이 잡아먹었다. 첫 번째는 상어가 물고기를 잡아먹으면, 해당 물고기의 방향을 상어가 새로 가지게 되는데 이걸
빼먹고 그냥 상어의 원래 방향 계속 가지고 가는 것으로 짜는 바람에(72행쯤에서) 틀린 답이 떴다. 두 번째는 상어가 처음에 먹은((0, 0)에 있는) 물고기
번호도 result에 합산시켜줘야 하는데(22행), 이걸 안 하는 바람에 답이 계속 틀리게 떴다. 이걸 모르고 fish_move shark_move 등등 다른 부분이 틀렸나
계속 검사해봤는데 틀린 부분이 없었고, 한참동안 개똥꼬쇼하다가 나중에 고쳤더니 맞는 답이 나왔다. 첫 번째 부분이야 그래도 금방 찾아서 고쳤는데 
두 번째 부분 때문에 진짜 너무 오래 걸림; 다음에는 이런 기본적인 초기 설정 관련 부분을 좀 꼼꼼히 살펴야할듯..
그리고 이번에 2차원 배열인 board의 값을 new_board에 복사해주는 과정에서 copy 함수를 사용했는데, algorithm 헤더파일에 있다는데 그거 추가 안 해도
써지는데 왜 그러는지는 모르겠다 어째됐든 이제 다차원 배열 복사할 때 copy 함수 잘 쓰면 될듯
*/