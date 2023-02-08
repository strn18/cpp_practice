#include <iostream>
#define MAX_N 15
#define MAX_A 1000000

using namespace std;

int N, L, R, X, count = 0;
int A[MAX_N];

void solve(int choice, int start);
bool check(int choice);
int bit_count(int bit);

int main(){
  scanf("%d %d %d %d", &N, &L, &R, &X);
  for(int i=0; i<N; i++)
    scanf("%d", &A[i]);
  
  solve(0, 0);

  printf("%d", count);

  return 0;
}

void solve(int choice, int start){
  if(start == N){
    if(check(choice))
      count++;
    return;
  }

  solve(choice, start+1);
  choice |= (1<<start);
  solve(choice, start+1);
}

bool check(int choice){
  if(bit_count(choice) < 2) return false;

  int sum = 0, hard = 0, easy = MAX_A+1;
  for(int i=0; i<N; i++){
    if((choice>>i) & 1){
      sum += A[i];
      if(A[i] > hard) hard = A[i];
      if(A[i] < easy) easy = A[i];
    }
  }
  
  if(sum<L || sum>R || hard-easy<X) return false;
  return true;
}

int bit_count(int bit){
  if(bit == 0) return 0;
  return bit%2 + bit_count(bit/2);
}

/*
크게 어렵지 않았던 비트마스킹 문제. 기본적으로는 브루트포스(또는 dfs라고 봐도 될듯) 탐색 문제인데, N개의 요소들을 고르는 조합을
다 찾아보면 된다. 이때, 조합이 조건을 만족하였다면, count를 증가시키면 된다. N이 최대 15밖에 되지 않아서, 그냥 bool 배열 만들어서 평범하게
풀어도 되었겠지만 일단 비트마스킹으로 풀어봤다.

0번~N-1번 문제를 어떻게 골랐는지를 뜻하는 choice가 있을 때, solve(choice, start)는 start번 문제를 고를 차례이다. 만약 끝까지 왔다면, 
지금까지 고른 조합(choice)이 조건에 만족한다면 count를 증가시키고, 아니면 그냥 리턴한다. 끝이 아니라면, 이번 문제를 안 고른 상태에서 다음
문제로 넘어가고, 이번 문제를 고른 다음에 다음 문제로 넘어간다. 즉, start번 문제를 고른 경우와 고르지 않은 경우를 모두 탐색한다.

check 함수에서, 고른 문제의 개수 즉 choice를 비트로 나타냈을 때 값이 1인 비트의 개수를 구하는 bit_count는 https://rebro.kr/63 여기의
집합의 크기 구하기 부분을 참고했다. 맨 오른쪽 비트의 값이 1이면, 2로 나눈 나머지가 1이고 0이면 나머지가 0인 것을 이용하여, 현재의 비트를
2로 나눈 나머지 + bit_count(현재의 비트/2) 를 재귀적으로 호출하는 방식이었다.
그리고 고른 문제의 난이도의 합과 최고난이도와 최저난이도의 차를 구하는 것은, 0번 비트 ~ N-1번 비트를 돌면서, 1과의 bit and 연산을 통해
i번 문제를 골랐는지 판단하고, 골랐으면 sum, hard, easy를 갱신해준다. 근데 쓰면서 생각난건데, 그냥 이 부분에 위의 bit_count 부분, 즉 
문제가 몇 개인지 세는 부분을 합쳤어도 됐을듯. 어쨌든 이걸 해서, sum, hard, easy가 조건에 맞으면 true를 리턴한다.

이렇게 따로 가지치기 없이 그냥 2^N가지 모든 경우를 다 탐색하도록 짜도, N이 최대 15니까 (2^15)*15(check 부분에서 N개의 비트를 돌테니까)
= 수십만 정도밖에 안 되기 때문에 풀 수 있었다. 만약에 N이 크다든가 하면, 가지치기 부분을 추가해야할 것 같다. 예를 들어, 지금까지 고른
문제 난이도의 합이 이미 R을 넘어버리면 바로 back 하는 방식으로..

다른 비트마스킹 풀이도 좀 찾아봤는데, https://leesh111112.tistory.com/111 여기가 좀 배울 점이 있었음. 나는 solve 함수의 인자로
choice를 계속 넘겨주는 방식으로 풀었는데, 여기서는 어차피 choice의 값이 [0 ~ 2^N-1] 이라는 것(나는 0-based라서 이렇고, 링크의 원래 
코드에서는 [1 ~ 2^N] 임)을 이용하여, 아예 그 값을 돌면서 그 안에서 고른 문제의 개수, sum, hard, easy를 구해주는 방식이었다. 엄청
짧고 간결했음.
*/