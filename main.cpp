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