#include <iostream>

using namespace std;

typedef struct{int height, ways, checked;}pos;
pos map[500][500];
int M, N;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int DP(int r, int c); // (r, c)의 ways를 리턴. 아직 없다면 값을 채워서 리턴.

int main(){
  scanf("%d %d", &M, &N);

  for(int i=0; i<M; i++){
    for(int j=0; j<N; j++){
      scanf("%d", &map[i][j].height);
      map[i][j].ways = 0;
      map[i][j].checked = 0;
    }
  }

  map[0][0].ways = 1;
  map[0][0].checked = 1;

  printf("%d", DP(M-1, N-1));

  return 0;
}

int DP(int r, int c){
  if(!map[r][c].checked){
    for(int i=0; i<4; i++){
      int nr = r+dr[i];
      int nc = c+dc[i];
      if(0<=nr&&nr<M && 0<=nc&&nc<N && map[nr][nc].height>map[r][c].height)
        map[r][c].ways += DP(nr, nc);
    }
    map[r][c].checked = 1;
  }
  return map[r][c].ways;
}

/*
dfs랑 섞인듯한 dp문제. 처음에는 백트래킹으로 풀어도 될까? 싶었는데, 그렇게 하나하나 찾으면 시간초과가 날 것 같았다.
그 다음에는 (0, 0)부터 시작해서, 상하좌우로 경로 수를 퍼뜨려나가듯이 bfs 비슷하게 풀면 되지 않을까? 싶었는데, 좀 생각해보니까
반대로 (M-1, N-1)부터 시작해서, 상하좌우의 값을 끌어다오는 느낌으로 재귀로 하면 더 편할 것 같았다.

dp[i][j]: (i, j)로 도달하는 경우의 수. 로 둔 다음, dp[i][j] = 상하좌우 중에서, 높이가 더 높은 칸의 dp값. 으로 점화식을 세웠다.
그 다음 DP 함수를 정의해서, (r, c)의 dp값을 이미 구했다면 그걸 리턴하고, 아직 안 구했다면 채워서 리턴하는 식으로 짰다.

처음에는 dp[i][j]가 0이 아니라면 dp값이 채워진 것으로 하려 했는데, 그렇게 하면 dp값이 원래 0이 맞는 애들(예제의 (1, 1)같은)은
그냥 0을 리턴하면 되는데, dp[i][j]가 0일 때 dp값이 아직 안 채워진 것으로 인식해버리니깐 상하좌우 dp값을 찾는 과정을 쓸데없이 반복하게 되었다. 
그래서 따로 구조체를 선언하여 그 안에 높이값, 경로 수(dp값)와 dp값을 찾았는지 판단하는 checked 변수를 넣어서 하나로 묶었다.

이후로는 높이를 입력받고 (0, 0)의 가짓수와 checked를 넣어준 다음 DP(M-1, N-1)을 출력하면 되었다. 38행에서 범위 나갔는지 체크해주는 부분을
까먹어서 한 번 틀렸으나 그거 수정하니 맞았음.
*/