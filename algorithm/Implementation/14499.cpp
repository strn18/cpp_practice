#include <iostream>
#define MAX 20

using namespace std;

int N, M;
int dice[6] = {0};
int board[MAX][MAX];
int dr[5] = {-99, 0, 0, -1, 1}; // 1~4: 동서북남
int dc[5] = {-99, 1, -1, 0, 0};
int rot[5][4] = {{}, {1, 2, 3, 5}, {5, 3, 2, 1}, {0, 5, 4, 2}, {2, 4, 5, 0}};

void rotation(int d);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int r, c, K;

  cin >> N >> M >> r >> c >> K;

  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      cin >> board[i][j];
  
  while(K--){
    int d;

    cin >> d;

    if(r+dr[d]<0 || N<=r+dr[d] || c+dc[d]<0 || M<=c+dc[d]) continue;

    r += dr[d]; c += dc[d];

    rotation(d);

    if(board[r][c] == 0)
      board[r][c] = dice[2];
    else{
      dice[2] = board[r][c];
      board[r][c] = 0;
    }
    
    cout << dice[5] << '\n';
  }

  return 0;
}

void rotation(int d){
  int temp = dice[rot[d][0]];

  for(int i=0; i<3; i++)
    dice[rot[d][i]] = dice[rot[d][i+1]];

  dice[rot[d][3]] = temp;
}

/*
걍 빡구현 문제. 주사위를 동 서 북 남 방향으로 굴릴 때, 주사위 여섯 칸들의 인덱스만 잘 변형해주면 됨. 나는 주사위의 여섯 칸을 dice에 담았고,
 0
123  인덱스에 따른 칸의 위치는 이렇게 생각했다. 즉 dice[2]가 바닥이랑 닿은 칸이고, dice[5]가 하늘을 보는 칸, dice[3]이 동쪽을 보는 칸임.
 4
 5
이 다음에, 동 서 북 남(주어지는 명령 1 2 3 4에 해당됨) 방향으로 굴릴 때, 주사위 값 바뀌는 것만 잘 생각해주면 된다. 동쪽이나 서쪽으로 굴릴 때는
인덱스 1 2 3 5의 값이 한 칸씩 밀려서 바뀌고, 북쪽이나 남쪽은 0 2 4 5의 값이 바뀜. 처음에는 동 서 북 남 마다 다 함수를 만들어줄까 했는데,
걍 순서 인덱스만 다른 거니까 그걸 rot에 넣고, 주어지는 명령 d를 rotation 함수의 인자로 넣어서, rot[d]의 네 숫자에 해당하는 인덱스의 값을
변형해주기로 함(이때 d는 1~4인 1 base니까, 그걸 맞춰주기 위해 rot[0]에는 걍 빈 값을 넣음).

주어지는 명령 d에 따라 주사위의 위치(r, c)를 이동시켰는데, 범위 밖이면 그냥 continue 한다(32행). 아니라면 위치 바꿔주고, 회전(rotation)
해준 다음, 주사위의 바닥의 값 이용하는 연산(38, 40행) 잘 해주고, 하늘을 바라보는 값 잘 출력해주면 됨.
*/