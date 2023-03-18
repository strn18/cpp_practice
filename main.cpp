#include <iostream>
#include <string>
#include <queue>

using namespace std;

int ans = 0;
int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
int seven_board[5][5] = {0};
string board[5];

void combination(int num, int doyeon, int princess);
bool check(int r, int c);

int main(){
  for(int i=0; i<5; i++)
    cin >> board[i];

  for(int i=0; i<19; i++)
    combination(i, 0, 0);
  
  printf("%d", ans);

  return 0;
}

void combination(int num, int doyeon, int princess){
  int r = num/5, c = num%5;

  if(board[r][c] == 'Y') doyeon++;
  if(doyeon > 3) return;

  seven_board[r][c] = 1;

  if(++princess == 7){
    if(check(r, c))
      ans++;
  }
  else{
    for(int i=num+1; i<25; i++)
      combination(i, doyeon, princess);
  }

  seven_board[r][c] = 0;
}

bool check(int r, int c){
  queue<pair<int, int>> Q;
  bool visited[5][5] = {false};
  int count = 0;

  Q.push({r, c});
  visited[r][c] = true;
  count++;

  while(!Q.empty()){
    int cur_r = Q.front().first, cur_c = Q.front().second;
    Q.pop();

    for(int i=0; i<4; i++){
      int next_r = cur_r+dr[i], next_c = cur_c+dc[i];
      
      if(0<=next_r && next_r<5 && 0<=next_c && next_c<5){
        if(seven_board[next_r][next_c] && !visited[next_r][next_c]){
          Q.push({next_r, next_c});
          visited[next_r][next_c] = true;
          count++;
        }
      }
    }
  }

  return (count == 7 ? true : false);
}