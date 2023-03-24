#include <iostream>
#include <queue>
#define MAX 50

using namespace std;

int R, C;
int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
char map[MAX][MAX];
queue<pair<int, int>> water, sonic;

void water_move();
int sonic_move();

int main(){
  int ret, minutes = 0;

  scanf("%d %d", &R, &C);

  for(int i=0; i<R; i++){
    for(int j=0; j<C; j++){
      cin >> map[i][j];

      if(map[i][j] == '*')
        water.push({i, j});

      else if(map[i][j] == 'S')
        sonic.push({i, j});
    }
  }

  while(true){
    minutes++;

    water_move();
    ret = sonic_move();

    if(ret == 0){
      printf("KAKTUS");
      return 0;
    }
    else if(ret == 2) break;
  }

  printf("%d", minutes);

  return 0;
}

void water_move(){
  int T = water.size();

  for(int t=0; t<T; t++){
    int r = water.front().first;
    int c = water.front().second;
    water.pop();

    for(int i=0; i<4; i++){
      int nr = r+dr[i];
      int nc = c+dc[i];
      
      if(0<=nr && nr<R && 0<=nc && nc<C){
        if(map[nr][nc]=='.' || map[nr][nc]=='S'){
          map[nr][nc] = '*';
          water.push({nr, nc});
        }
      }
    }
  }
}

int sonic_move(){
  int T = sonic.size();

  for(int t=0; t<T; t++){
    int r = sonic.front().first;
    int c = sonic.front().second;
    sonic.pop();

    for(int i=0; i<4; i++){
      int nr = r+dr[i];
      int nc = c+dc[i];

      if(0<=nr && nr<R && 0<=nc && nc<C){
        if(map[nr][nc] == 'D') return 2;

        if(map[nr][nc] == '.'){
          map[nr][nc] = 'S';
          sonic.push({nr, nc});
        }
      }
    }
  }

  return (sonic.empty() ? 0 : 1);
}