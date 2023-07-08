#include <iostream>
#define MAX 10000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, count = 0;
  int A[MAX];

  cin >> N >> M;

  for(int i=0; i<N; i++)
    cin >> A[i];

  int s = 0, e = 0, sum = 0;

  while(true){
    if(sum >= M) sum -= A[s++];
    else if(e == N) break;
    else sum += A[e++];

    if(sum == M) count++;
  }

  cout << count;

  return 0;
}

/*
부분합인줄 알고 풀었는데 투포인터였던 문제. 근데 부분합으로 푼 것도 맞긴 했음(첫번째 제출). 다만 부분합으로 풀면, 일단 부분합 배열을 채우는 거는
O(N)으로 끝나지만, 나중에 모든 구간의 부분합을 M과 비교하는 부분에서 O(N^2)이 된다. 그래서 계산 시간이 좀 걸림.

투포인터로 푸니깐 0ms로 맞았다. 제일 기본적인 투포인터 문제 형태임. 근데 투포인터에서 포인터 두 개(여기서는 s, e)를 다루는 게 생각이 잘 안나서
https://blog.naver.com/kks227/220795165570 여기 참고하면서 풀었음. 나는 포인터 두 개를 통한 부분합이 A[s]~A[e]를 다 더하는 걸로 잡고서
풀었었는데(두번째 제출), 틀려서 위 블로그 글 보면서 다시 공부하니깐, A[s]~A[e-1]을 더하는 것이었음([s, e) 구간의 합).
*/