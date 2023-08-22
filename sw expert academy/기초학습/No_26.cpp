// 수 만들기
#include <iostream>
#include <queue>
#define MAX 10

using namespace std;

typedef struct{
  int added, left;
} info;

struct compare{
  bool operator()(info a, info b){
    return a.added > b.added;
  }
};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  for(int tc=1; tc<=T; tc++){
    int N, K, ans = 0;
    int A[MAX];
    priority_queue<info, vector<info>, compare> pq;

    cin >> N;

    for(int i=0; i<N; i++)
      cin >> A[i];
    
    cin >> K;

    pq.push({0, K});

    while(true){
      info cur = pq.top();
      pq.pop();

      if(cur.left == 0){
        ans = cur.added;
        break;
      }

      pq.push({cur.added + cur.left, 0});

      for(int i=0; i<N; i++)
        pq.push({cur.added + (cur.left % A[i]), cur.left / A[i]});
    }

    cout << '#' << tc << ' ' << ans << '\n';
  }

  return 0;
}

/*
반대로 생각하는 것이 중요했던 문제. 나는 X=0에서부터 시작해서, D에 적절한 A[i]를 곱하거나 X += D를 해주면서 K를 가장 빠르게 만들려고 했다.
근데 시간초과가 나서 https://blog.youhogeon.com/38 여기랑 https://nankisu.tistory.com/38 여기 풀이를 보니까, 반대로 생각하는 게 중요했음. 

K = 14, A = {3} 이라고 하자. 이때, 링크 속 알고리즘(또는 이 코드에서 39행)을 돌리게 되면, pq의 top에는 {0, 14}가 있었을 것이고, 
51행까지 돌리게 되면 pq에는 새로 {14, 0}과 {2, 4}가 들어갔을 것이다. 이때, {14, 0}은 무슨 뜻이냐? 앞으로 0으로 줄여야 하는 수
(남은 양, left)가 14가 남았었는데, 그걸 그냥 1씩 더하는 걸 14번 하겠다는 소리임. 이건 어렵지 않다.
그렇다면 {2, 4}는? 남은 양이 14가 남았었는데, 그걸 이제 A[0] = 3을 D에 곱해서 줄여주겠다는 소리다. 즉, 1+1+...+1 로 14를 만드는 게 아니라, 
1+1+3+3+3+3 으로 14를 만든다는 소리. 그러므로, 3으로 14를 나눴을 때 나머지인 2는 먼저 D=1일 때 두 번 미리 해주고, 그 다음에 D에 3을 곱해서, 
이제 네 번 해줘야 하니까 {2, 4}를 pq에 넣는 거다.

설명이 좀 장황한데, 링크 참조해서 잘 생각해봐야 함/
*/