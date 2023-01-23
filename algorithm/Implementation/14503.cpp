#include <iostream>
#define MAX 50

using namespace std;

int N, M, count = 0;
int board[MAX][MAX]; // 0: 빈 칸, 1: 벽, 2: 청소한 칸
int dr[8] = {-1, 0, 1, 0, -1, 0, 1, 0}; // 북, 동, 남, 서
int dc[8] = {0, 1, 0, -1, 0, 1, 0, -1};

void clean(int r, int c, int d);

int main(){
  int first_r, first_c, first_d;

  scanf("%d %d", &N, &M);
  scanf("%d %d %d", &first_r, &first_c, &first_d);
  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      scanf("%d", &board[i][j]);

  clean(first_r, first_c, first_d);

  printf("%d", count);

  return 0;
}

void clean(int r, int c, int d){
  int next_r, next_c, next_d;
  bool flag = false;

  board[r][c] = 2;
  count++;

  while(1){
    for(int i=d+3; i>=d; i--){
      if(0<=r+dr[i] && r+dr[i]<N && 0<=c+dc[i] && c+dc[i]<M && board[r+dr[i]][c+dc[i]] == 0){
        next_r = r+dr[i]; next_c = c+dc[i]; next_d = i%4;
        flag = true;
        break;
      }
    }

    if(flag) break;

    r += dr[d+2]; c += dc[d+2];
    if(board[r][c] == 1)
      break;
  }

  if(flag)
    clean(next_r, next_c, next_d);
}

/*
알고리즘은 쉽지만(문제에 써있는 그대로 하면 됨), 코드로 옮기는 게 좀 귀찮았던 구현 문제(처음 풀어봄). 
그냥 어떠한 칸에 로봇 청소기가 있을 때, 왼쪽 방향부터 반시계방향으로 보고, 청소할 곳이 있으면 청소하고 없으면 후진한 다음 또 반시계방향으로 
보고... 를 반복한다. 그러다 후진도 못하면(뒷 칸이 벽이면) 작동을 멈춘다.
이걸 구현하기 위해 d방향을 본 상태에서 (r, c)를 청소하는 함수인 clean을 사용했다. 우선 청소를 하고 count를 늘려준 다음, 위의 과정을 해본다.
왼쪽부터 반시계방향으로 봤는데 청소할 칸이 있으면 next_r, next_c에 위치를 담고 이때 방향을 next_d에 담는다. 만약 없다면, 47행으로 와서, 한 칸
뒤로 간다(dr과 dc가 북동남서 순이라서, 인덱스에 +2를 해주면 뒷 방향을 가리키게 됨). 뒷 칸이 벽이면 작동 끝이니까 break한다.
while문에서 나와서, flag가 참이라면 아까 청소할 칸을 찾은 거니까 다시 clean을 실행해주면 된다.

d의 왼쪽 방향부터 시계방향으로 도는 것을 구현하기 위해, dr와 dc 배열을 4칸이 아니라 8칸으로 만들었다. 이렇게 한 다음, d+3부터 시작해서 네 번을
돌면 됨. 예를 들어, 방향이 동쪽일 경우 d가 1이니까, 4 3 2 1 순으로 돌게 되어서 북 서 남 동 순으로 돌게 된다. 이렇게 안 하고 배열을 4칸으로 
만들어버리면 좀 복잡해짐.

제출하니 맞았다. 근데 처음에는 48행에 뒷 칸이 범위를 벗어나는지도 체크했었는데, 나중에 문제 좀 읽어보니까 보드의 경계는 무조건 1(벽)이라고 한다. 
그래서 범위 벗어나는지는 체크할 필요 없으니까 수정해서 제출했더니 맞음.


다른 사람들은 dfs 문제라고도 하던데, 아예 연관이 없는 건 아니지만 dfs라고 하기엔 좀 그렇고, 빡구현 문제에 가까운 것 같아서 구현으로 분류함.
*/