// 기초 BFS 연습(5. 그래프)
#define MAX 10

typedef struct{int x, y, count;} info;
info Q[MAX*MAX];
int front, rear; // front == rear라면 Q는 empty.

int board_size;

int ori_board[MAX+1][MAX+1]; // 0: 빈 칸, 1: 벽, 2: 방문함
int board[MAX+1][MAX+1];

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

void push_q(int x, int y, int count){ // Q의 size는 MAX*MAX이기에, 절대 꽉차지 않음.
  Q[rear++] = {x, y, count};
}

info pop_q(void){
  info ret = Q[front++];

  return ret;
}

bool out_of_bound(int x, int y){
  if(x<=0 || board_size<x || y<=0 || board_size<y) return true;
  else return false;
}

void bfs_init(int map_size, int map[10][10]) {
  board_size = map_size;

  for(int i=0; i<map_size; i++)
    for(int j=0; j<map_size; j++)
      ori_board[i+1][j+1] = map[i][j];
}

int bfs(int x1, int y1, int x2, int y2) {
  for(int i=1; i<=board_size; i++)
    for(int j=1; j<=board_size; j++)
      board[i][j] = ori_board[i][j];
  
  front = 0; rear = 0;
  
  push_q(x1, y1, 0);

  while(front != rear){
    info cur = pop_q();

    if(cur.x == x2 && cur.y == y2) return cur.count;

    for(int i=0; i<4; i++){
      int nx = cur.x + dx[i];
      int ny = cur.y + dy[i];

      if(!out_of_bound(nx, ny) && board[ny][nx] == 0){
        push_q(nx, ny, cur.count + 1);
        board[ny][nx] = 2;
      }
    }
  }

  return -1;
}

/*
구현하기 귀찮아서 안 풀다가 푼 문제. 걍 기본 bfs 문제이지만, <queue>를 쓸 수가 없어 직접 큐를 구현해야 했다. 매우 귀찮..

우선 큐의 타입을 구조체로 만들고(이때, {x좌표, y좌표, count값}으로 만들었다. (x, y)로 방문하는 데 드는 횟수가 count였다는 뜻), 
해당 타입으로 큐를 만들었는데, 배열을 통해 구현했다. 이후 push와 pop 함수도 따로 만들었는데, 큐(배열)의 크기를 MAX*MAX로 선언하여, 
절대 꽉찰 일이 없도록 하였다. board의 크기가 최대 MAX*MAX이므로, 꽉찰 일은 없음.

이렇게 되니깐 push와 pop을 구현하기 쉬웠다. 나머지 연산도 해줄 필요 없고(사실 첫번째 풀이에서 하긴 했는데 마지막 풀이에서는 걍 지움), 
꽉찰 일 없으니깐 오버플로우 걱정할 필요 없고, 비었을 때 pop을 할 일도 없으니깐 언더플로우도 걱정 ㄴㄴ. 그래서 그냥 push할 때는 rear++, 
pop할 때는 front++을 해주었다.

나머지는 그냥 기본 bfs 문제 생각하면 된다. 처음 시작점부터 상하좌우 탐색으로 뻗어나가면서, 도착점을 찾았을 경우 count 값을 리턴.
*/