#include <iostream>
#define MAX 500

using namespace std;

int N, M, maximum = -1;
int board[MAX][MAX];
int dr[3] = {-1, 1, 0};
int dc[3] = {0, 0, 1};
bool visited[MAX][MAX] = {false};

void dfs(int r, int c, int count, int depth); // 지금까지 밟은 수 합은 count, 밟은 칸 개수는 depth개.
void pink_t(int r, int c); // 분홍색 ㅜ 모양 도형

int main(){
  scanf("%d %d", &N, &M);

  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      scanf("%d", &board[i][j]);

  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      dfs(i, j, 0, 0); // 분홍색 도형 제외하고 4개의 도형을 놓는 경우를 따진다.
      pink_t(i, j);
    }
  }

  printf("%d", maximum);
  
  return 0;
}

void dfs(int r, int c, int count, int depth){
  visited[r][c] = true;
  count += board[r][c];
  depth++;

  if(depth < 4){
    for(int i=0; i<3; i++){
      int nr = r+dr[i];
      int nc = c+dc[i];
      if(0<=nr && nr<N && 0<=nc && nc<M && !visited[nr][nc])
        dfs(nr, nc, count, depth);
    }
  }
  else
    maximum = max(maximum, count);

  visited[r][c] = false;
}

void pink_t(int r, int c){
  int count;
  int dr[2][4] = {{0, 0, 0, 1}, {0, 0, 0, -1}}; // dr[0]과 dc는 ㅜ 모양, dr[1]과 dc는 ㅗ 모양
  int dc[4] = {0, 1, 2, 1};

  for(int i=0; i<2; i++){ // 한 번은 dr와 dc를 그대로 더해주고, 한 번은 바꿔서 더해준다(점대칭)
    for(int j=0; j<2; j++){ // 한 번은 dr값을 그대로 더해주고, 한 번은 부호를 바꿔서 더해준다(축 대칭)
      count = 0;
      for(int k=0; k<4; k++){
        int nr = r;
        int nc = c;

        if(i==0){
          nr += dr[j][k];
          nc += dc[k];
        }
        else{
          nr += dc[k];
          nc += dr[j][k];
        }

        if(nr<0 || N<=nr || nc<0 || M<=nc) // 범위를 벗어났으면 도형을 놓을 수 없으니, 더 이상 볼 필요 없음
          break;

        count += board[nr][nc];
      }
      maximum = max(maximum, count);
    }
  }
}

/*
백준에 브루트포스로 분류되어있어서 그렇게 분류해놨지만, dfs에 좀 더 가까운듯한 문제. 풀이 방식은 간단하게 떠올릴 수 있으나 구현이 ㅈ같다.

우선 처음에는 진짜 ㄹㅇ 브루트포스 방식으로, 5가지 도형과 각 도형을 뒤집고 회전했을 때의 경우를 다 따져서, 각 경우의 dr과 dc값을 구해내서
풀어야하나? 싶었는데, 좀 해보니까 너무 복잡했음. 

그래서 좀 생각을 해봤는데, 자세히 보니깐 각 도형들의 대칭/회전을 하며 놓았을 때 먹을 수 있는 칸은 dfs를 통해 구할 수 있다. 즉 어떠한 칸을
대상으로, 그 칸에 각 도형의 끝부분을 놨을 때 먹게되는 칸은, 그 칸을 시작으로 깊이 4의 dfs를 쳤을 때 방문하게되는 칸과 같다. 그럼 그 칸에
도형의 끝부분이 아니라 중간 부분을 놨을 때 먹게되는 칸은 어케 계산하나? 라고 할 수도 있는데, 어차피 그 경우는 그 근처 칸에 도형의 끝부분을
놨을 때 먹게되는 칸이랑 같으니까, 그 근처 칸을 계산하면서 구해짐. 그렇기 때문에, 모든 칸에 대해 깊이 4의 dfs를 쳐주고, 깊이 4일 때 최댓값을
갱신해주는 식으로 하면 풀 수 있다.

근데 이렇게 하면 문제가 하나 생긴다. 다른 도형들은 위에서 말한 dfs 방식을 썼을 때 먹게되는 칸을 구할 수 있는데, 핑크색 도형은 못 구한다.
핑크색 도형의 어느 칸에서 시작하든, 깊이 4 dfs로 핑크색 도형을 만들 수 없기 때문.. 그래서 그 경우는 그냥 따로 만들었다.
(r, c)에 핑크색 도형을 놓는 경우를 모두 계산하는 pink_t 함수를 선언했다. 그 다음, 핑크색 도형을 회전/대칭할 수 있으니깐, ㅜ ㅗ ㅏ ㅓ 모양을 
다 따질 수 있도록 했다. (i, j)가 (0, 0)이면 ㅜ, (0, 1)이면 ㅗ, (1, 0)이면 ㅏ, (1, 1)이면 ㅓ 이다.
왜 이렇게 되나? dr[0]과 dc는 ㅜ 모양을 가지도록 하는 위치값인데, dr[0]의 부호값을 반대로 한 dr[1]과 dc를 쓰면, r의 부호값이 반대로 가는 
거니까 x축에 대칭이 된다. 그래서 ㅗ 모양이 됨. 그리고 i가 0일 때는 그거 그대로이고, i가 1일 때는 69행에 의해 r과 c를 반대로 더해준다. 
이렇게 하면, 점대칭이 된다고 볼 수 있음. 그래서 ㅜ, ㅗ -> ㅏ, ㅓ 가 된다.

제출하니 맞았다. 근데 잘 생각해보니까, dfs 부분에서 dr과 dc를 굳이 상하좌우 다 쓸 필요가 없다. 상하우 만 쓰면 됨. 왜냐? 좌 방향으로 dfs 치는
경우는, 그 윗칸들이나 아랫칸들에서 계산해줄 거임. 그러니까 중복으로 계산해줄 필요가 없다. 이 부분 수정하고 제출하니 시간 줄어들었음(마지막 제출).
*/