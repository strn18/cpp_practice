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