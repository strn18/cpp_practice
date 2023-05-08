#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int gear[4][8];
int rot[2][8] = {{0, 1, 2, 3, 4, 5, 6, 7}, {7, 6, 5, 4, 3, 2, 1, 0}}; // 반시계, 시계로 돌릴 때의 인덱스 준비

void rotation(int num, int dir, int spread); // spread가 -1이면 왼쪽, 0이면 양쪽, 1이면 오른쪽으로 전파

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int K, total = 0;

  for(int i=0; i<4; i++){
    string temp;

    cin >> temp;

    for(int j=0; j<8; j++)
      gear[i][j] = temp[j]-'0';
  }

  cin >> K;

  while(K--){
    int num, dir;

    cin >> num >> dir;

    rotation(num-1, dir, 0); // 주어지는 톱니바퀴 번호는 1-based이므로 0-based로 변환
  }

  for(int i=0; i<4; i++)
    total += gear[i][0]*(int)pow(2, i);

  cout << total;

  return 0;
}

void rotation(int num, int dir, int spread){
  if(spread<=0 && 0<=num-1 && gear[num-1][2]!=gear[num][6]) // 왼쪽 톱니바퀴로 회전 전파
    rotation(num-1, dir*(-1), -1);
  if(spread>=0 && num+1<=3 && gear[num][2]!=gear[num+1][6]) // 오른쪽 톱니바퀴로 회전 전파
    rotation(num+1, dir*(-1), 1);
  
  if(dir == -1) dir = 0; // rot[0]이 반시계이므로, dir을 맞춰줌

  int temp = gear[num][rot[dir][0]];
  for(int i=0; i<7; i++)
    gear[num][rot[dir][i]] = gear[num][rot[dir][i+1]];
  gear[num][rot[dir][7]] = temp;
}

/*
어렵진 않은 구현 문제. i번 톱니바퀴의 극을 gear[i][0]~gear[i][7]에 담았음. 맨 위 톱니가 gear[i][0]이고, 순서는 시계방향임.

좌우 톱니바퀴의 인접한 톱니와 비교하면서 회전을 전파해주면 된다. 이때 회전을 담당하는 함수는 rotation으로, num번 톱니바퀴를 dir 방향으로
회전하게 됨. 이때, 46행과 48행에서 좌우 톱니바퀴로 회전을 전파해주는데, 오른쪽으로부터 회전을 전파받은 톱니바퀴가 다시 오른쪽으로 전파하면
안 되는데 처음에 그걸 간과했었음. 이후 그거 제한 걸어주기 위해 spread 인자를 추가했다.

14499번이랑 비슷했다. 회전할 때, 방향에 따른 인덱스 순서를 배열(여기서는 rot)에 담아둔 것도 비슷했음. 
*/