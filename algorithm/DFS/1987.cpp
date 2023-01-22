#include <iostream>
#include <string>
#define MAX 20

using namespace std;

int R, C, answer = -1;
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
bool visited[26] = {false};
string board[MAX];

void dfs(int r, int c, int count);

int main(){
  scanf("%d %d", &R, &C);

  for(int i=0; i<R; i++)
    cin >> board[i];
  
  dfs(0, 0, 0);

  printf("%d", answer);

  return 0;
}

void dfs(int r, int c, int count){
  visited[board[r][c]-'A'] = true;
  answer = max(answer, count+1);

  for(int i=0; i<4; i++){
    int nr = r+dr[i], nc = c+dc[i];
    
    if(0<=nr && nr<R && 0<=nc && nc<C)
      if(!visited[board[nr][nc]-'A'])
        dfs(nr, nc, count+1);
  }
  visited[board[r][c]-'A'] = false;
}

/*
어렵지 않았던 dfs + 백트래킹 문제. 한 번 밟은 알파벳은 다시 못 밟으므로, 알파벳 26개에 대해서 visited 배열을 만들고, 4방향에 대해 dfs를 돌려주면
된다. 다음 칸이 1) 범위 안이고, 2) 다음 칸의 알파벳을 아직 안 밟았다면(visited가 false라면), 다음 칸에 dfs를 실행해주는 방식이다.
이때 해당 칸으로의 dfs가 끝나면, 이번 칸에서 밟았다고 표시했던 알파벳을 안 밟은 것으로 바꿔주는 방식(39행)으로 백트래킹을 쳐주면 된다.
*/