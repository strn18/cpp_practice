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