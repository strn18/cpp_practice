#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int K, bigR = 0, bigC = 0, smallR, smallC;
  int dir[6], len[6];

  cin >> K;

  for(int i=0; i<6; i++){
    cin >> dir[i] >> len[i];

    if(i%2) bigR = max(bigR, len[i]);
    else bigC = max(bigC, len[i]);
  }

  for(int i=0; i<6; i++){
    if(dir[i] == dir[(i+2)%6] && dir[(i+1)%6] == dir[(i+3)%6]){
      smallR = len[(i+1)%6];
      smallC = len[(i+2)%6];
      break;
    }
  }

  cout << ( (bigR * bigC) - (smallR * smallC) ) * K;

  return 0;
}

/*
은근 귀찮았던 문제. 주어지는 6개 변의 방향이 4 2 3 1 3 1 과 같은 형태일 때, 4 2에 해당하는 부분은 전체 직사각형의 가로와 세로에 해당하고 
3 1 3 1에 해당하는 부분은 나머지 4개 변임. 이때, 중간 1 3 부분이 바로 작은 직사각형(파인 부분)의 가로와 세로이다. 이를 이용하여, 전체 
직사각형의 가로와 세로 길이를 곱한 값에서 작은 직사각형의 가로와 세로 길이를 곱한 값을 빼면 넓이를 구할 수 있다.
*/