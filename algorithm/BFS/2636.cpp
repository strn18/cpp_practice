#include <iostream>
#define MAX 100

using namespace std;

int N, M;
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
int curBoard[MAX][MAX];
int nextBoard[MAX][MAX];

bool outOfBound(int r, int c);
void copyBoard(void); // nextBoard에서 curBoard로 복사
int countCheese(void); // curBoard에서 치즈 개수 세기
void setAir(int r, int c); // nextBoard의 (r, c)가 현재 구멍(0)이라면 -1로 바꾸고 인접에 대해서도 dfs.

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int time = 0, curCheese = 0, prevCheese = 0;

  cin >> N >> M;

  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      cin >> nextBoard[i][j];
      
      if(nextBoard[i][j] == 1)
        ++curCheese;
    }
  }

  setAir(0, 0);
  copyBoard();

  while(curCheese > 0){
    ++time;
    prevCheese = curCheese;

    for(int i=0; i<N; i++){
      for(int j=0; j<M; j++){
        if(curBoard[i][j] != 1) continue;

        bool melt = false;

        for(int k=0; k<4; k++){
          int r = i + dr[k];
          int c = j + dc[k];

          if(!outOfBound(r, c) && curBoard[r][c] == -1){
            melt = true;
            break;
          }
        }

        if(!melt) continue;

        nextBoard[i][j] = -1;

        for(int k=0; k<4; k++){
          int r = i + dr[k];
          int c = j + dc[k];

          if(!outOfBound(r, c) && curBoard[r][c] == 0)
            setAir(r, c);
        }
      }
    }

    copyBoard();

    curCheese = countCheese();
  }

  cout << time << '\n' << prevCheese;
  
  return 0;
}

bool outOfBound(int r, int c){
  if(r<0 || N<=r || c<0 || M<=c) return true;
  else return false;
}

void copyBoard(void){
  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      curBoard[i][j] = nextBoard[i][j];
}

int countCheese(void){
  int count = 0;

  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      if(curBoard[i][j] == 1)
        ++count;
  
  return count;
}

void setAir(int r, int c){ // nextBoard의 (r, c)가 현재 구멍(0)이라면 -1로 바꾸고 인접에 대해서도 dfs.
  if(nextBoard[r][c] != 0) return;

  nextBoard[r][c] = -1;

  for(int i=0; i<4; i++){
    int nr = r + dr[i];
    int nc = c + dc[i];

    if(!outOfBound(nr, nc) && nextBoard[nr][nc] == 0)
      setAir(nr, nc);
  }
}

/*
나는 dfs로 풀었는데, 태그도 bfs로 되어있고 bfs로 훨씬 쉽게 푸는 방법이 있어서 bfs로 분류함.

내가 푼 방식은 다음과 같다.
curBoard의 모든 칸을 돌면서, 해당 칸이 치즈(1)일 경우, 상하좌우 중 하나라도 공기(-1)라면 그 칸은 녹고, 그 칸과 인접한 구멍(0)들은 
공기로 바뀌게 된다. 그러므로, 해당 칸이 치즈일 경우 47행에서 인접칸에 공기가 있는지 검사해주고, 공기가 있다면 해당 칸은 공기(-1)로 바꾸고, 
61행에서 해당 칸과 인접한 구멍 칸들을 공기로 바꿔주었다. 이때, 바뀌는 것은 다음 턴에 적용해야 하므로, nextBoard 값이 바뀌도록 했다. 그런 다음, 
모든 칸을 다 돌면 nextBoard의 값들을 curBoard로 복사해준다. 

이렇게 푼 다음, 다른 풀이 찾아보니까 https://ongveloper.tistory.com/159 여기에 훨씬 쉽게 푸는 법이 있었음. 
그냥 매 시간마다 (0, 0)에서 bfs를 시작해서, 인접한 공기 칸으로 뻗어나가면서 치즈 칸을 발견하면 그걸 공기 칸으로 바꿔주는 방식이다. 이렇게 하면, 
공기 말고 구멍 칸이랑만 인접한 치즈는 녹을 일이 없다. 왜냐? 걔가 녹으려면 그 구멍 칸으로 bfs가 뻗어나가야 하는데, 구멍 칸은 치즈에 둘러쌓여 
있으므로 (0, 0)에서 시작한 bfs가 거기까지 갈 수가 없음. 
*/