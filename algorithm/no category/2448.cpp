#include <iostream>

using namespace std;

bool isStar(int H, int r, int c);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  cin >> N;

  if(N == 3){
    cout << "  *  \n";
    cout << " * * \n";
    cout << "*****\n";
  }
  else{
    for(int i=0; i<N; i++){
      for(int j=0; j<2*N-1; j++)
        cout << (isStar(N, i, j) ? '*' : ' ');

      cout << '\n';
    }
  }

  return 0;
}

bool isStar(int H, int r, int c){
  if(H == 3){
    if(r == 1 && c == 2) return false;
    else return true;
  }

  if(H-1 - r <= c && c < H + r){
    if(r < H/2) return isStar(H/2, r, c - (H/2));

    if(r <= c && c < 2*H-1 - r) return false;
    else return isStar(H/2, r % (H/2), c % H);
  }
  else return false;
}

/*
어려운 별찍기 문제. 나는, 어떠한 좌표값이 별인지 공백인지를 isStar 함수로 확인하고, 출력하도록 하였다.
isStar은 높이가 H인 삼각형(그리고 그 양옆 공백을 포함하여 사각형 모양) 안에 (r, c)가 있을 때, 그게 별이면 true를 리턴한다.
이때, (r, c)의 위치를 크게 세 부분으로 나눌 수 있다.
1) 삼각형 양 옆 빈 공간. 44행에 해당한다.
2) 삼각형 안쪽 빈 역삼각형 공간. 41행에 해당한다.
3) 나머지, 삼각형 내부 소형 삼각형 3개 공간. 위쪽 하나가 39행, 아래쪽 두 개는 42행에 해당한다.
그리고 H가 3이 되었을 경우, (1, 2)면 공백, 아니면 별이다. 그럼 그거 말고 그 양옆 공간에 해당될 경우는 어떡해?
N이 3으로 주어진 게 아닌 이상, 그럴 리는 없다. 그 전 isStar 함수가 호출되었을 때, 1)에 해당되어서 이미 false를 리턴했을 것임.
N이 3인 경우는 걍 예외로 빼놨다.

아래는 풀면서 메모해둔 내용임 참고 ㄱㄱ


어떠한, 높이 K의 삼각형이 있다고 하자. (K = 6, 12, ...)

가운데 영역에 속하려면? (0-based)
1) K/2, K/2+1, ..., K-1 행에 속할 때, 각각
2) [K/2, (2*K-1) - K/2), [K/2+1, (2*K-1) -(K/2+1)), ..., [(K-1, (2*K-1) - (K-1)) 열에 속한다.
이럴 경우, 공백이다.

외부 영역(왼쪽, 오른쪽)에 속하려면?
1) i행에 속할 때,
2) [K-1 - i, K + i)에 속하지 않으면 된다.
이럴 경우, 공백이다.

내부 세 삼각형에 속하면? 해당 삼각형을 기준으로 좌표를 바꿔서 재귀 ㄱㄱ
언제까지? 위 두 가지 케이스에 속하거나, 삼각형의 높이 K가 3이 될 때까지.
K가 3이 되었다면, (1, 2)면 공백, 아니면 *이다.


다 풀고나서 https://ansohxxn.github.io/boj/2448/ 여기를 참고해봤는데, 좀 더 쉬운 풀이 같아 보임.
별 or 공백을 저장하는 2차원 전체 배열을 만들어 우선 공백을 다 넣어두고, 삼각형의 모서리를 계속 별로 바꿔가면서 재귀치는 방식임.
*/