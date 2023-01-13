#include <iostream>

using namespace std;

int R, C;
string board[10000];

bool put_pipe(int r, int c);
bool able(int r, int c);

int main(){
  int count = 0;

  scanf("%d %d", &R, &C);
  for(int i=0; i<R; i++)
    cin >> board[i];

  for(int i=0; i<R; i++)
    if(put_pipe(i, 0))
      count++;

  printf("%d", count);

  return 0;
}

bool put_pipe(int r, int c){
  board[r][c] = 'x';
  if(c == C-1) return true;

  for(int row=r-1; row<=r+1; row++){
    if(able(row, c+1))
      if(put_pipe(row, c+1))
        return true;
  }
  
  return false;
}

bool able(int r, int c){
  if(0<=r && r<R && board[r][c]=='.')
    return true;
  return false;
}

/*
그리디+백트래킹 문제.
처음에 생각한 방식은 다음과 같다. 0행부터 R-1행까지 돌면서, 어떠한 행의 맨 왼쪽 열부터 시작하여, 최대한 위쪽 방향으로 탐색을 한다.
즉, (r, c)에 파이프를 세운 다음, (r+1, c+1), (r, c+1), (r-1, c+1) 순으로 훑으면서, 만약 able한 칸이 있다면 바로 그쪽으로 넘어가서 파이프를
세운다. 그리고 그 넘어간 칸에서도 똑같이 우측의 상중하 순으로 훑으면서 able한 칸이 있으면 또 바로 넘어간다. 이런 식으로 해서, 맨 끝 열(C-1열)까지
연결되었다면, count++ 해준다. 
이 방식으로 해서 예제도 다 맞아서 제출했는데, 틀렸다고 떴다. 사실 이 방시에는 문제점이 있는데, 다음 열로 넘어갈 때 상 쪽으로 우선 갔다가 거기서
앞으로 진행하다가 막히면, 이제 아예 못 가는 것으로 판단하고 put_pipe가 false를 리턴해버린다는 것. 즉,
...x.x.
.xx.xx.
.xxx.x.
.xxxx..
.xxxxx.
이런 보드가 있을 때, (0, 0)에서 시작하면 (0, 0), (0, 1), (0, 2), (1, 3), (0, 4) 순으로 갔다가 더 이상 갈 곳이 없어서 false를 리턴해버린다.
하지만 실제로는 (1, 3)에서 (2, 4)로 가면 길이 있음. 즉 답은 1이 되어야 하지만 내 코드는 0을 출력함.

이것을 해결하기 위해, 도중에 막힌다면 바로 false를 리턴하지 않고, 뒷 칸으로 돌아가는 백트래킹 방식을 섞었다.
put_pipe도 행과 열을 인자로 받는 식으로 변경함. 만약 다음 열의 상중하를 다 탐색해봤는데, 모두 true를 리턴하지 못할 경우(상중하 모두 도중에
길이 막힐 경우), false를 리턴한다. 만약 도중에 true를 리턴할 경우(맨 끝 열까지 이어졌을 경우), true를 리턴한다. 

이 방식으로 제출해봤는데 시간 초과가 떴다. return false를 해주기 전에 board[r][c]를 다시 '.'으로 바꿔주는 부분이 있었는데, 그것 때문에
어차피 안 되는 경우를 계속 반복해서 탐색하는 바람에 시간 초과가 뜬듯. 근데 어차피 어떠한 칸을 x로 바꿨을 때, 그 칸이 결국 false를 리턴하게
된다면, 그 칸에서 마지막 열까지 이어지는 것은 불가능하다는 뜻이다. 그렇기에 x로 바꿔준 걸 다시 .으로 바꿔줄 필요가 없음.

그래서 그 부분 지우고 제출했더니 맞았다.
*/