/*
#include <iostream>
#include <queue>

using namespace std;

typedef struct{int h, r, c;}pos;

queue<pos> new_tomato;
int box[100][100][100];

int dh[6] = {-1, 1, 0, 0, 0, 0};
int dr[6] = {0, 0, 1, -1, 0, 0};
int dc[6] = {0, 0, 0, 0, -1, 1};

int H, N, M;
int count = 0;

void bfs(void);
int all_riped(void); // box 안에 0이 하나도 없으면 1 반환

int main(){
  scanf("%d %d %d", &M, &N, &H);
  for(int i=0; i<H; i++)
    for(int j=0; j<N; j++)
      for(int k=0; k<M; k++){
        scanf("%d", &box[i][j][k]);
        if(box[i][j][k] == 1)
          new_tomato.push({i, j, k});
      }

  if(all_riped()){
    printf("0");
    return 0;
  }
  
  bfs();

  if(!all_riped()){
    printf("-1");
    return 0;
  }

  printf("%d", count);
  
  return 0;
}

void bfs(void){
  while(1){
    int n = new_tomato.size();
    for(int i=0; i<n; i++){
      for(int j=0; j<6; j++){
        int newh = new_tomato.front().h+dh[j];
        int newr = new_tomato.front().r+dr[j];
        int newc = new_tomato.front().c+dc[j];
        if(0<=newh && newh<H && 0<=newr && newr<N && 0<=newc && newc<M){
          if(!box[newh][newr][newc]){
            new_tomato.push({newh, newr, newc});
            box[newh][newr][newc] = 1;
          }
        }
      }
      new_tomato.pop();
    }
    if(new_tomato.empty())
      break;
    count++;
  }
}

int all_riped(void){
  for(int i=0; i<H; i++)
    for(int j=0; j<N; j++)
      for(int k=0; k<M; k++)
        if(!box[i][j][k])
          return 0;
  return 1;
}

7576의 3차원 버전 문제로, 2차원을 3차원으로만 바꾸면 돼서 크게 어려울 건 없었으나 bfs 부분을 좀 바꿨는데 그 부분에서 약간 헷갈린 점이 있었음. 7576 풀이들과 다르게 큐를 두 개 만들지 않고 그냥 하나만 만든 다음에 51~52행처럼 큐의 사이즈를 미리 다른 변수에 넣어두고, 그 사이즈 만큼만 for문을 돌며 큐에 새로 익는 토마토 위치를 넣고, 위치 넣는 과정이 끝나면 사용한 토마토(저번에 익은 토마토) 위치는 큐에서 pop하는 식으로(64행) 풀었다. 초기 코드에서는 66~68행이 없었고 대신 while문이 while(!new_tomato.empty())였는데, 이렇게 짜니까 토마토들은 이미 다 익었는데 count 값이 1 증가하게 되는 문제가 발생함. 그래서 while(1)로 바꾸고, 토마토들이 다 익은 상태에서 new_tomato가 비워지는 과정(64행 반복 과정)이 끝난 후 66행에 if문을 넣어서 break하는 식으로 바꿨다. 근데 이렇게 하니까 32~35행에서의 예외처리가 필요 없어졌고 그 부분 주석처리하고 제출하니까 맞았음. 
그리고 문제 풀면서 좌표가 x축 y축 z축 세 개라 구조체 정의하고 사용했고, 29행처럼 중괄호로 묶는 거 처음 써봤는데 편한 것 같다.
*/