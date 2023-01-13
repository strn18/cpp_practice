/*
#include <iostream>
#include <queue>
//#include <utility> 단독으로 pair를 사용할 때는 필요하지만 queue의 속성으로 사용할 때는 필요 없음

using namespace std;

int tomato[1000][1000];
int check[1000][1000] = {0};
int dx[4] = {0, 1, 0, -1}; // 위, 오른, 아래, 왼
int dy[4] = {-1, 0, 1, 0}; // 위, 오른, 아래, 왼
int row, col; // 상자의 세로, 가로
int cnt = 0; // 날짜 세기
queue<pair<int, int>> curQ, nextQ; // (세로, 가로) 임.

void bfs(int x, int y);

int main(){
  cin >> col >> row;
  for(int r=0; r<row; r++)
    for(int c=0; c<col; c++)
      cin >> tomato[r][c]; 
  // 토마토 정보 입력 다 끝난 다음에,
  for(int r=0; r<row; r++)
    for(int c=0; c<col; c++)
      if(tomato[r][c] == 1)
        bfs(c, r); // 다음 날 정보 미리 넣기
  
  curQ = nextQ;
  nextQ = queue<pair<int, int>>();

  while(!curQ.empty()){
    cnt++; // 하루 지난 상황이니까
    
    while(!curQ.empty()){
      pair<int, int> p = curQ.front();
      curQ.pop();
      bfs(p.second, p.first);
    }
    
    curQ = nextQ; // 다음 날 준비
    nextQ = queue<pair<int, int>>();
  }

  // 이제 더 이상 변화가 없는 건데,
  for(int r=0; r<row; r++)
    for(int c=0; c<col; c++)
      if(tomato[r][c] == 0){ // 한 칸이라도 덜 익었다면 다 못 익는 상황인 것
        cout << -1;
        return 0;
      }

  cout << cnt; // 그게 아니라면 다 익는데 며칠 걸린 건지 출력
  return 0;
}

void bfs(int x, int y){
  tomato[y][x] = 1;
  for(int i=0; i<4; i++)
    if(0 <= x+dx[i] && x+dx[i] < col && 0 <= y+dy[i] && y+dy[i] < row)
      if(tomato[y+dy[i]][x+dx[i]] == 0 && !check[y+dy[i]][x+dx[i]]){ // 인접 칸에 토마토가 있고 안 익었으며, 그 칸을 아직 체크하지 않았으면
        nextQ.push(pair<int, int>(y+dy[i], x+dx[i])); // 다음 날 익게 하고
        check[y+dy[i]][x+dx[i]] = 1; // 그 칸 체크해두기
      }
}

스터디 3주차에서 BFS 배우면서 소개된 문제임. dfs문제인 1012랑 좀 비슷함. 혼자 나름 잘 풀긴 했는데 딱 하나 어이 없는 부분에서 틀려서 많이 애먹었다. 62행에서 (y+dy[i], x+dx[i])를 푸시해야 하는데 실수로 (y, x)를 푸시하는 걸로 코드를 짜놓는 바람에, 왜 틀린지도 모르고 한참 고민했음. 그리고 처음에는 check 배열 없이 그냥 했었는데, 문제가 풀리긴 했으나 메모리 초과가 났음. 사실 그렇게 풀면서도 check 배열 안 쓰면 중복이 생긴다는 건 알고 있었는데 어차피 상하좌우 네 방향이니까 끽해야 4배만 차이날 것 같아서 초과는 절대 안 날 줄 알았음. 근데 초과나서 결국 추가했다. 
*/