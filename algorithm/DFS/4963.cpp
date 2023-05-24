#include <iostream>
#define MAX 50

using namespace std;

int h, w;
int board[MAX][MAX]; // 1: 섬, 0: 바다, -1: visited 섬

void dfs(int r, int c);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while(true){
    int count = 0;

    cin >> w >> h;

    if(!w) break;

    for(int i=0; i<h; i++)
      for(int j=0; j<w; j++)
        cin >> board[i][j];
    
    for(int i=0; i<h; i++){
      for(int j=0; j<w; j++){
        if(board[i][j]==1){
          count++;
          dfs(i, j);
        }
      }
    }

    cout << count << '\n';
  }

  return 0;
}

void dfs(int r, int c){
  board[r][c] = -1;

  for(int i=r-1; i<=r+1; i++){
    for(int j=c-1; j<=c+1; j++){
      if(i<0 || h<=i || j<0 || w<=j) continue;
      
      if(board[i][j]==1) dfs(i, j);
    }
  }
}

/*
기초 dfs/bfs 문제.
*/