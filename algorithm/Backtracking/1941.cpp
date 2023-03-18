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

/*
개 ㅈ같았던 문제. 

우선 처음에는, 25명 중에서 7명을 고르는, 25C7 조합을 다 고르는 방식으로 하면 시간초과가 날 것 같아서, dfs+백트래킹으로 풀어보았다.
즉, 어떤 학생에서 시작해서, 그와 인접한 상하좌우로 뻗어나가면서 총 7명을 고르는데, 도중에 도연파가 3명을 초과하면 뒤로 돌아가는(가지치기)
방식이다. 그러다 총 7명을 고르게 되면 ans++ 해준다.
근데 이렇게 하니까 답이 제대로 안 나옴. 좀 생각해보니, 힌트의 두번째 케이스 같은 경우는 내가 생각한 dfs 방식으로는 나올 수 없음(도중에
두 갈래로 뻗어나감). 그래서, 현재 노드의 상하좌우로 뻗어나가는 방식이 아니라, 지금까지 고른 공주 노드의 상하좌우로 뻗어나가는 방식으로 바꿨다.
근데 이렇게 하니까, 모든 케이스를 다 구할 수는 있는데 중복이 많이 생긴다. 힌트의 두번째 케이스를 예로 들면, (1, 0), (1, 1)을 구한 다음에,
(1, 2)를 먼저 구하고 (2, 1)을 구하는 거랑 그 반대 순서로 구하는 거랑, 어차피 최종 고른 노드는 똑같아지는데, 순서가 달라서 다 중복으로 
세어버린다. 그래서 아니 어떻게 하는 거지? 하면서 고민하다가, 그냥 ㅈㄴ 비효율적이지만 일단 방법을 생각해봄. 뭐냐면, 그동안 고르는 케이스들을
저장해두고, 7명을 다 골랐다면 이번에 고른 케이스를 그 저장해둔 케이스들이랑 하나하나 비교하면서, 겹치는 게 있으면 넘어가고 없으면 새로운
케이스로 추가해주는 방식임.
이렇게 하니까 매우 복잡하게 나오긴 하는데, 일단 짜보긴 했다 그랬더니 맞긴 했음(첫번째 제출).

근데 시간도 오래 걸리고 아무리 생각해도 이건 아닌 것 같아서 다른 풀이를 봤다. https://yabmoons.tistory.com/117 여기를 봤는데, 그냥 
25C7을 다 구하는 방식이었음. 조합 계산기 돌려보니까, 그거 다 해봤자 48만 정도밖에 안 됨 씨발! 그래서 나도 그 방식으로 바꿨다.

그냥 dfs로 단순히 25C7가지 경우를 모두 구하고(물론 도중에 가지치기를 위해 도연파가 3명 초과가 되면 return함), 7명을 다 구했다면, check 함수로
검사해준다(노드들이 하나로 인접해있는 형태인지). 근데 이 check 함수를 잘못 생각해서 시간을 ㅈㄴ 날려먹었음. 처음에는 모든 노드가 다른 한 노드와
인접(상하좌우)한다면, 옳은 형태(하나로 이어진)라고 생각했다. 근데 생각해보니까, 둘 씩 인접한 노드가 다른 노드들과 떨어져있으면 하나로 이어진 게
아님;; 그래서 bfs로 이걸 검사해주는 방식으로 바꿨다. 검사하는 건 그냥 쉬움. 공주로 뽑힌 노드 하나에서 bfs를 시작한 다음, 모든 공주 노드(7개)에
다 도달하면 true이고, 그렇지 않으면 떨어져있는 거니까 false이다.

돌아보니 그렇게 어려운 문제는 아닌데 시간 ㅈㄴ 잡아먹었다.
*/