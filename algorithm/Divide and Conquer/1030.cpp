#include <iostream>
#include <cmath>

using namespace std;

int N, K;

bool is_black(int r, int c, int start_r, int start_c, int len);

int main(){
  int s, r1, r2, c1, c2, length;

  scanf("%d %d %d %d %d %d %d", &s, &N, &K, &r1, &r2, &c1, &c2);

  length = pow(N, s);

  for(int i=r1; i<=r2; i++){
    for(int j=c1; j<=c2; j++)
      printf("%d", (is_black(i, j, 0, 0, length) ? 1 : 0));
    printf("\n");
  }

  return 0;
}

bool is_black(int r, int c, int start_r, int start_c, int len){
  if(len == 1) return false;

  int edge = len/N; // 주어진 공간을 N*N으로 나눴을 때, 나뉜 한 변의 길이
  int white = (N-K)/2; // 주어진 공간의 끝에서, 가운데 K*K 까지의 변의 개수

  for(int i=start_r; i<start_r+len; i+=edge){
    for(int j=start_c; j<start_c+len; j+=edge){
      if(r < i+edge && c < j+edge){
        if(start_r+(edge*white) <= r && r < start_r+len-(edge*white) 
        && start_c+(edge*white) <= c && c < start_c+len-(edge*white))
          return true;
        else if(edge != 1)
          return is_black(r, c, i, j, edge);
        else
          return false;
      }
    }
  }
  return true; // this won't be excuted
}

/*
좀 역겹지만 풀만했던 분할정복 문제. 매 단위 시간이 진행될 때마다, 도형을 N*N개의 정사각형으로 분할하고, 가운데 K*K개의 정사각형은 검은색으로
칠한다. 그렇지 않은 정사각형들은 다시 N*N개로 분할한다. 이걸 s번 진행한다.

내가 푼 방식은 다음과 같다. 가로 세로 길이가 len이고 시작점이 (start_r, start_c)인 범위 내에 있는 어떠한 점 (r, c)가 있다. 이 점이 가운데
부분에 해당된다면 true를 리턴하고, 그렇지 않다면 해당되는 부분(N*N개로 분할된 부분)에 대해서 다시 재귀를 쳐준다. 이걸 해주는 함수인
is_black을 정의했다. 함수 내에서, edge는 분할된 부분의 변의 길이이다. white는, 가령 N이 5이고 K가 3이면, 5*5의 분할된 부분 중 가운데
3*3 부분이 검은색으로 칠해지는데, 이때 위아래 남는 부분의 개수인 2에 해당된다. 즉, 주어진 범위의 끝에서 K*K 부분 까지의 변의 개수이다.

우선 (r, c)가 N*N개의 부분 중 어디에 해당되는지 찾아본다. i와 j를 start_r과 start_c에서 시작해서, 매번 edge만큼 증가시켜주면 됨.
(r, c)가 어느 부분에 해당되는지 찾았으면(34행), K*K 부분에 해당되는지 판단한다(35, 36행). 거기에 해당된다면 true를 바로 리턴하고, 그렇지
않다면 start_r과 start_c 대신 i와 j를 넣고, len도 edge로 바꿔서 재귀를 친다. 즉 분할된 작아진 부분에 대해서 다시 재귀를 치는 거임.
근데 만약 edge가 1이라면 base condition이다(더 이상 분할 불가). 그러면 false를 리턴. 45행에 넣은 거는, 저거 안 넣으면 VScode가 리턴값
없을 수도 있다고 판단해서 약한 오류 뜨길래(실행은 됨) 걍 넣었음. 어차피 저기까지 안 간다.

좀 더 쉽게 설명하자면, 주어진 흰색 정사각형을 N*N개로 분할 하는 것을 s번 반복하니까, 총 범위(좌표?)는 (0, 0)부터 ((s^N)-1, (s^N)-1)이 된다.
이 범위에서, 구하고자 하는 위치((R1, C1)부터 (R2, C2)의 점들)를 is_black에 인자로 넣으면, is_black은 가운데 K*K 부분에 해당되면 true를
리턴하고, 그렇지 않으면 계속 N*N 분할하면서 재귀를 친다. 그러다가 base_condition(edge가 1)에 다다르면 false를 리턴한다.

이렇게 제출하니까 80% 정도에서 시간초과가 났다. 왜 그랬나 보니, s=0일 때, is_black에 len가 1로 들어오면서 무한재귀를 한다. 그래서 27행에
len가 1이면 바로 false를 리턴하도록 했더니 맞았음.

https://myprivatestudy.tistory.com/27 이 풀이를 봤는데, 엄청 간단하게 풀었다. 내 32, 33행 for문처럼 N*N개의 부분 중에 어디에 해당되는지
구하는 걸 하지 않고, 그냥 바로 K*K에 해당되면 true 리턴, 그렇지 않으면 범위 줄여서 재귀를 시행함. 
그리고 이거 보면서 안 건데, 내 코드에서굳이 40행을 넣을 필요가 없다. 왜냐? edge가 1이라면, 39행에서 재귀를 칠 때 len 인자로 edge를 주니까 
1이 들어가는데, 그러면 27행에서 어차피 false를 리턴하게 됨. 그거 지우고 제출해봤더니 맞았다.
*/