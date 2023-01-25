#include <iostream>
#include <deque>
#define MAX 100

using namespace std;

typedef struct{int r, c;} pos;

int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};

void change_direction(char C, int* direction);

int main(){
  int N, K, L;
  int direction = 0, count = 0;
  int board[MAX][MAX] = {0};
  char change_info[10001] = {0};
  deque<pos> snake;

  scanf("%d", &N);
  scanf("%d", &K);
  for(int i=0; i<K; i++){
    int a, b;
    scanf("%d %d", &a, &b);
    board[a-1][b-1] = 1;
  }
  scanf("%d", &L);
  for(int i=0; i<L; i++){
    int X;
    char C;
    scanf("%d %c", &X, &C);
    change_info[X] = C;
  }

  snake.push_front({0, 0});

  while(1){
    int nr = snake.front().r;
    int nc = snake.front().c;
    count++;

    if(change_info[count-1] != 0)
      change_direction(change_info[count-1], &direction);

    nr += dr[direction];
    nc += dc[direction];

    if(nr<0 || N<=nr || nc<0 || N<=nc || board[nr][nc] == 2)
      break;

    if(board[nr][nc] == 0){
      pos tail = snake.back();
      snake.pop_back();
      board[tail.r][tail.c] = 0;
    }

    snake.push_front({nr, nc});
    board[nr][nc] = 2;    
  }

  cout << count;

  return 0;
}

void change_direction(char C, int* direction){
  if(C == 'L')
    (*direction)--;
  else
    (*direction)++;

  if((*direction) < 0)
    (*direction) += 4;
  else if((*direction) > 3)
    (*direction) -= 4;
}

/*
문제에 주어진 조건을 그대로 구현하면 되었던 구현 문제. 그렇게 어렵지는 않았다. 매 1초마다 뱀의 상태를 바꿔주어야하는데, 이때 뱀의 정보를 나타내기
위해 덱을 사용했다. 뱀은 어차피 1초에 한 칸씩 움직이니까, 덱의 front를 머리, back을 꼬리로 생각하고, 움직일 때마다 front에 새로운 위치를 넣어주고
back에서 원소 하나를 빼주면 된다. 이때, 사과를 먹었다면 길이가 늘어나는 거니까 back에서 원소를 빼지 않는다. 

뱀이 바라보는 방향을 direction 변수에 담았고, 이때 0 1 2 3은 각각 우 하 좌 상을 나타낸다. 그리고 뱀이 이동할 위치를 구하기 위해 dr와 dc배열을 
썼고, 인덱스 0~3은 마찬가지로 각각 우하좌상 이다. 뱀의 머리 위치에다가 directino을 인덱스로 써서 dr와 dc값을 더해주면, 그 값이 곧 뱀이 이동할
위치가 된다. 해당 위치가 범위를 벗어나거나, 이미 뱀이 위치하고 있다면(board값이 2) 이동을 종료한다(49행). 만약 비었다면 꼬리를 pop하고, 원래 
꼬리가 있던 칸의 board는 비었으니까 0으로 바꿔준다. 그러고 나서, 해당 위치 값을 머리로 넣어주고 board값을 2로 바꿔준다. 

그리고 뱀의 방향 변환 정보는 change_info 배열에 담았는데, change_info[x]가 c라면, x초가 지난 후 c에 따라서 방향을 바꾼다는 뜻이다(c가 널이라면
방향을 안 바꾸는 것이고, L이면 왼쪽, D면 오른쪽). 근데 여기서 헷갈리면 안 되는 게, 입력으로 X와 L이 주어졌다면, X초에 이동이 끝나고 나서 왼쪽으로
방향을 바꾼다는 것이다. X초가 되었을 때 왼쪽으로 바꾸는 게 아님. 그래서 43행에서 count초에 이동하기 전에(머리로 넣을 위치값을 찾기 전에), count-1
인덱스의 change_info값을 보고 머리 방향을 바꾸는 것. 왜냐면, count-1초 이동이 끝나고 나서 change_info[count-1]에 따라 머리 방향을 바꾸니깐.

제출했는데 처음에는 틀렸다. 알고보니, 입력으로 주어지는 X가 최대 10000이니까, 그걸 인덱스로 쓰는 change_info 배열은 길이가 10000이 넘어야 하는데,
100으로 선언해버렸음. 방향 변환 횟수(입력으로 주어지는 X의 개수)인 L과 헷갈렸음. 수정하고 제출하니 맞았다.
*/