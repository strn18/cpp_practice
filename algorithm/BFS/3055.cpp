#include <iostream>
#include <queue>
#define MAX 50

using namespace std;

int R, C;
int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
char map[MAX][MAX];
bool visited[MAX][MAX] = {0};
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

      if(0<=nr && nr<R && 0<=nc && nc<C && !visited[nr][nc]){
        if(map[nr][nc] == 'D') return 2;

        if(map[nr][nc] == '.'){
          map[nr][nc] = 'S';
          sonic.push({nr, nc});
          visited[nr][nc] = true;
        }
      }
    }
  }

  return (sonic.empty() ? 0 : 1);
}

/*
그리 어렵지 않았던 bfs 문제. 조건이 이것저것 있긴 한데 풀만했다.

매 턴마다 물과 고슴도치를 4방향으로 이동시켜주면 된다. 이때, 물은 동굴(D)와 바위(X)를 제외한 곳으로 갈 수 있고, 고슴도치는 물(*)과 바위(X)를
제외한 곳으로 갈 수 있다. 근데 물이 이번 턴에 갈 곳으로 고슴도치(S)는 못 가니까, 물을 먼저 이동시켜주면 된다.

whlie문 안에서 매 턴 minutes를 증가시키고, 물 이동 함수인 water_move를 실행시킨 다음 고슴도치 이동 함수인 sonic_move를 실행시킨다. 이때,
sonic_move는 이번 이동 때 고슴도치가 D에 도착했다면 2를, 이동할 곳이 없다면 0을, 그게 아니라면 1을 리턴한다.

water_move와 sonic_move는 거의 유사함. 현재의 위치들(각 queue에 넣었음)을 4방향으로 한 칸 이동시킨다. 이때 물은 .이나 S인 곳으로 이동할 수
있고, 고슴도치는 .이나 D로 이동할 수 있다. 근데 고슴도치는 한 번 갔던 칸으로 갈 필요가 없으니 visited로 검사해준다. 근데 이거 쓰면서 생각난 건데,
고슴도치가 한 번 갔던 칸이라면 그 값이 *이거나 S일텐데, 그러면 애초에 .이나 D가 아니니까 걸러지겠네..? visited를 쓸 필요가 없는 것 같기도 함. 
어쨌든, 고슴도치를 이동시킨 다음, queue가 empty라면? 이번 턴에 아무 곳으로도 이동 못 한 것이니까 0을 리턴하고, 아니면 1을 리턴한다.

visited 걍 없애버리고 제출하니까 그거도 맞았음.
*/