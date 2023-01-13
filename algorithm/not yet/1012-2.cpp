#include <iostream>
#include <string.h>

using namespace std;

int cab[50][50];
int visit[50][50];
int worms, M, N;

int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

void DFS(int ypos, int xpos);

int main(){
  int T, K;
  int x, y;

  cin >> T;
  for(int i=0; i<T; i++){
    memset(cab, 0, 50*50*sizeof(int));
    memset(visit, 0, 50*50*sizeof(int));
    worms = 0;
    
    cin >> M >> N >> K;
    for(int j=0; j<K; j++){
      cin >> x >> y;
      cab[y][x] = 1;
    }
    
    for(int r=0; r<N; r++)
      for(int c=0; c<M; c++)
        if(cab[r][c] && !visit[r][c]){
          worms++;
          DFS(r, c);
        }
        
    cout << worms << endl;
    worms = 0;
  }
  return 0;
}

void DFS(int ypos, int xpos){
  if(visit[ypos][xpos] || !cab[ypos][xpos])
    return;
  
  visit[ypos][xpos] = 1;
  int newY, newX;
  
  for(int i=0; i<4; i++){
    newY = ypos+dy[i];
    newX = xpos+dx[i];
    if(0<=newY && newY<N && 0<=newX && newX<M)
      DFS(newY, newX);
  }
}

/*
전역 후 공부하면서 다시 풀어봤다. 원래 풀이랑 큰 차이는 없고, '이미 탐색했거나 배추가 없는 칸'을 DFS에 진입하고 바로 return 하면서 
제외해주느냐(이 풀이), 아니면 상하좌우 dfs 돌릴 때 제외해주느냐(원래 풀이)의 차이였다.
*/