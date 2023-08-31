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