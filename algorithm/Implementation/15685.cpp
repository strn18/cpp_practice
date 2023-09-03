#include <iostream>
#include <vector>
#define MAX 100

using namespace std;

bool board[MAX+1][MAX+1] = {false};
int dr[4] = {0, -1, 0, 1};
int dc[4] = {1, 0, -1, 0};

pair<int, int> makeDragonCurve(int r, int c, int d, int g);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, ans = 0;

  cin >> N;
  
  while(N--){
    int x, y, d, g;

    cin >> x >> y >> d >> g;

    makeDragonCurve(y, x, d, g);
  }

  for(int i=0; i<MAX; i++)
    for(int j=0; j<MAX; j++)
      if(board[i][j] && board[i][j+1] && board[i+1][j] && board[i+1][j+1]) ++ans;

  cout << ans;

  return 0;
}

pair<int, int> makeDragonCurve(int r, int c, int d, int g){
  board[r][c] = true;

  if(g == 0){
    int nextR = r + dr[d];
    int nextC = c + dc[d];

    board[nextR][nextC] = true;

    return {nextR, nextC};
  }

  pair<int, int> mid = makeDragonCurve(r, c, d, g-1);

  int endR = mid.first + (c - mid.second);
  int endC = mid.second + (mid.first - r);

  makeDragonCurve(endR, endC, (d+3)%4, g-1);

  return {endR, endC};
}

/*
귀찮은 구현 문제. 

어떠한 점 (r, c)에서 d 방향으로 시작하는 3세대 dc(드래곤 커브)를 찍으려면?
우선 (r, c)에서 d 방향으로 2세대 dc를 찍는다. 그 도착점(다 찍고 난 끝점)을 (a, b)라고 하자. (a, b)를 기준점으로 하여, (r, c)를 시계 방향으로 
90도 회전한 점을 구한다. 그 점을 시작점으로 해서, d를 시계 방향으로 90도 회전한 방향으로 2세대 dc를 찍으면 끝이다.

그렇다면 (a, b)를 기준점으로 하여, (r, c)를 시계 방향으로 90도 회전한 점은 어떻게 구할까?
(r, c)에서 (a, b)로 향하는 벡터는 (a-r, b-c)인데, 이를 이용하여 구할 수 있다. 좌표평면에서 벡터 잘 계산해보면, (a + (c-b), b + (a-r)) 이라는 
것을 알 수 있음. 이제 위에서 말했다시피, (a + (c-b), b + (a-r))을 시작점으로 2세대 dc를 d 방향을 시계 방향으로 90도 돌린 방향으로 찍으면 된다.

이때, (a, b)도 구해야 한다. 이를 위해, dc를 찍는 함수인 makeDragonCurve()가 찍고 난 끝점을 pair<int, int>로 리턴하도록 했다.
위의 내용을 바탕으로 makeDragonCurve()를 재귀적으로 호출하여 board에 dc를 찍어줬다(board[i][j]가 true라면 그 점은 드래곤 커브의 일부인 것).
base condition으로, g가 0이면 어차피 선분 하나이므로 그냥 그 방향으로 한 칸 가서 dc를 찍었음.

이렇게 한 다음, 31행에서는 점이 아니라 어떠한 정사각형을 보고, 그 꼭짓점의 board 값이 모두 true이면 ans를 증가시켜줬음.
*/