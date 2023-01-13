/*
#include <iostream>
#include <algorithm>
#include <string.h> // memset을 쓰기 위해

using namespace std;

int cab[50][50]; // cab[y][x]는 (x, y)에 배추가 있는지 여부
int visit[50][50]; // visit[y][x]는 (x, y)에 배추가 있을 때 거기에 방문했는지(그룹에 포함되었는지) 여부
int col, row; // 배추밭의 가로, 세로 길이
int dx[4] = {0, 1, 0, -1}; // 위, 오른쪽, 아래, 왼쪽 방향 나타내기 위한 변화값
int dy[4] = {-1, 0, 1, 0}; // 위, 오른쪽, 아래, 왼쪽 방향 나타내기 위한 변화값

void dfs(int x, int y); // 배추가 있는 (x, y)를 방문

int main(){
  int T;
  int K, worms;
  cin >> T;

  while(T--){
    cin >> col >> row >> K;
    worms = 0;

    memset(cab, 0, 50*50*sizeof(int)); // col*row*sizeof(int)라고 하면 안 된다.
    memset(visit, 0, 50*50*sizeof(int)); // 마찬가지.
    
    int x, y;
    while(K--){
      cin >> x >> y;
      cab[y][x] = 1; // (x, y)에 배추가 있음을 표시
    }

    for(int r=0; r<row; r++){
      for(int c=0; c<col; c++){ // 모든 땅을 돌면서,
        if(cab[r][c] && !visit[r][c]){ // 거기에 배추가 있고 방문을 안 했다면, 
          worms++; // 새로운 배추 그룹이 생긴 거니까 지렁이 1마리 추가하고 방문하기.
          dfs(c, r);
        }
      }
    }

    cout << worms << endl;
  }
  
  return 0;
}

void dfs(int x, int y){
  visit[y][x] = 1; // (x, y)를 방문했음을 표시

  for(int i=0; i<4; i++) // (x, y)의 위, 오른쪽, 아래, 왼쪽 땅이
    if(0 <= x+dx[i] && x+dx[i] < col && 0 <= y+dy[i] && y+dy[i] < row) // 배추밭을 초과하지 않고, 
      if(cab[ y+dy[i] ][ x+dx[i] ] && !visit[ y+dy[i] ][ x+dx[i] ]) // 거기에 배추가 있고 방문을 안 했다면, 
        dfs(x+dx[i], y+dy[i]); // 현재 배추 그룹에 포함되는 거니까 지렁이는 추가하지 않고 방문하기.
}

알고리즘 스터디 2주차에서 dfs 배우면서 9466과 함께 소개된 문제. 난이도는 그거보다 쉽긴 했지만 위, 오른쪽, 아래, 왼쪽 탐색을 위해 dx, dy 변화값을 사용해야 했기에 그거 관련해서 좀 까다로웠다. 사실 까다롭기보다는 좀 귀찮았음. 스터디에서 dx dy 쓰라는 팁 안 줬으면 ㅈㄴ 귀찮게 코드 짰을듯. 
cab과 visit이 2차원 배열이었기에, 얘네들 값 리셋을 위해 memset을 사용했다. 근데 25, 26번째 줄에서 무지성으로 col*row*sizeof(int) 라고 범위 잡아서 리셋하려다가 틀렸었음. 
만약 int a[2][4]라는 배열이 있고, 이 배열의 가로 3칸 세로 2칸을 리셋하겠답시고 3*2*sizeof(int) 이렇게 하면 
XXXX
XXXX
이 배열이
OOOX
OOOX
이렇게 리셋되는게 아니라, 그냥 처음부터 6칸이 리셋됨.
OOOO
OOXX
이렇게. 사실 당연한 건데 무지성으로 2차원 배열 리셋하려다 틀렸다. 그래서 그냥 배열 전체 다 리셋하는 식으로 바꿨음 어차피 크기 작아서 시간 초과 안 나니까.
*/