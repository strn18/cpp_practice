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