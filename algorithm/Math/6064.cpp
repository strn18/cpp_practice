#include <iostream>

using namespace std;

void swap(int *a, int *b);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  while(T--){
    int M, N, x, y, high;
    int count = 0;

    cin >> M >> N >> x >> y;

    if(M > N){
      swap(&M, &N);
      swap(&x, &y);
    }

    high = x;

    count += x;
    
    while(high != y){
      high -= (N-M);
      count += M;
      
      if(high <= 0) high += N;

      if(high == x){
        count = -1;
        break;
      }
    }

    cout << count << '\n';
  }

  return 0;
}

void swap(int *a, int *b){
  int temp = *a;
  *a = *b;
  *b = temp;
}

/*
M, N, x, y = 10, 12, 3, 9 라고 하자. 어떠한 해인 <low, high> 가 <3, 3>일 때, 10년이 지나면? <3, 1>이 된다. 또 10년 뒤엔? <3, 11>이 된다.
즉, M년이 지날 때마다, high는 (N-M)만큼 줄어든다. 그렇게 계속 줄이면서 high == y가 되는 지점을 찾으면 된다. 만약 찾지 못하고 계속 사이클
(무한반복)이 돈다면? -1을 출력하면 된다.

이를 위해 우선 M, N, x, y를 입력받고, M<N인 상황을 만들어주었다(21행). 그런 다음, 해를 <x, x>로 초기 설정 해주고 그만큼 count에 더해준다.
그러고 나서 high == y가 될 때까지 high에서 (N-M)만큼 계속 빼주면서 count를 증가시켜주면 된다. 근데 만약 high가 다시 x랑 같아진다면? 사이클이
형성된 것이다. 

첨에는 쫌 헷갈렸는데 풀어보니 크게 어렵진 않았던 문제.
*/