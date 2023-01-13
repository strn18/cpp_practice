/*
#include <iostream>
#include <queue>

using namespace std;

typedef struct{int r, c;}pos;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
int maze[100][100] = {0};
queue<pos> nextQ;

int N, M;

void bfs(void);

int main(){
  char temp;
  
  scanf("%d %d", &N, &M);
  getchar();
  
  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      scanf("%c", &temp);
      maze[i][j] = temp-'0'-1;
    }
    getchar();
  }
  maze[0][0] = 1;
  nextQ.push({0, 0});

  bfs();

  printf("%d", maze[N-1][M-1]);
  
  return 0;
}

void bfs(void){
  while(1){
    int n = nextQ.size();
    for(int i=0; i<n; i++){
      pos cur = nextQ.front();
      
      for(int j=0; j<4; j++){
        int newr = cur.r+dr[j];
        int newc = cur.c+dc[j];
        
        if(0<=newr && newr<N && 0<=newc && newc<M && maze[newr][newc]==0){
          maze[newr][newc] = maze[cur.r][cur.c]+1;
          
          if(newr==N-1 && newc==M-1)
            return;
          
          nextQ.push({newr, newc});
        }
      }
      nextQ.pop();
    }
  }
}

이거도 별로 어려운 문제는 아니었고, maze 배열에 '이동할 수 없는 칸에 -1, 아직 안 간 칸에 0, N번째로 방문한 칸에 자연수 N'을 넣기 위해서 입력받을 때 원래의 입력값인 1과 0에서 1만큼 뺀 값을 넣어준 거 말고는 특이한 거 없었음. 
*/