// 중간값 구하기(7. Heap)
#include <iostream>
#include <queue>
#define MOD 20171109

using namespace std;

void swap(int *a, int *b);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    int N, A, total = 0;
    priority_queue<int> max_pq;
    priority_queue<int, vector<int>, greater<int>> min_pq;

    cin >> N >> A;

    min_pq.push(A);

    while(N--){
      int X, Y;

      cin >> X >> Y;

      if(X > Y) swap(&X, &Y);

      if(X >= min_pq.top()){
        min_pq.push(X);
        min_pq.push(Y);

        max_pq.push(min_pq.top());
        min_pq.pop();
      }
      else if(Y >= min_pq.top()){
        max_pq.push(X);
        min_pq.push(Y);
      }
      else{
        max_pq.push(X);
        max_pq.push(Y);

        min_pq.push(max_pq.top());
        max_pq.pop();
      }

      total = (total + min_pq.top()) % MOD;
    }

    cout << '#' << t << ' ' << total << '\n';
  }

  return 0;
}

void swap(int *a, int *b){
  int temp = *a;
  *a = *b;
  *b = temp;
}

/*
백준에서도 봤던 건데(1655번), 못 풀었던 문젠데 여기서 풀었다. 

처음에는 그냥 pq 하나만 쓰면 된다고 생각했다. 우선 A를 pq에 넣어주고, 그 다음부터는 X, Y를 입력받아 pq에 넣은 후, 거기서 처음에는 1번, 그 다음에는 
2번, ..., 마지막에는 N번 pop을 해준 후(이때 pop해준 수들은 따로 저장해둔다), 그때 pq.top이 중앙값이다. 그런 다음 pop해준 수들을 다시 push해준다.

근데 이렇게 푸니깐 시간초과가 남. 사실 1번, 2번, ..., N번이면 총 O(N^2)번이라 당연히 시간초과인데 생각을 잘못했다.

어떻게 풀지 고민하다가, max_pq와 min_pq를 동시에 쓰는 방법으로 생각해냈음. 우선, A를 min_pq에 넣는다. 이때 max_pq와 min_pq의 사용 목표는, 
min_pq의 size가 max_pq보다 반드시 1만큼 더 크도록 유지한다. 그리고 min_pq의 수들은 모두 max_pq의 수들보다 크다. 이렇게 한다면, 중앙값은 반드시 
min_pq.top이다. 

이를 위해, 두 수 X, Y에 대해서(이때 Y가 X보다 크다고 가정한다), 만약 X와 Y가 모두 min_pq.top 이상이라면, 둘 다 min_pq에 넣어줄 수 있지만, 둘 다 
넣어버린다면 min_pq의 size가 1만큼만 더 커야하는데 그걸 초과해버린다. 그러므로, 우선 넣어준 후 min_pq.top을 빼서(걔가 min_pq의 최솟값이니깐), 
max_pq에 넣어준다. 이렇게 하면 min_pq의 size가 1만큼만 크도록 유지할 수 있다.
만약 Y만 min_pq.top 이상이라면, X는 max_pq에, Y는 min_pq에 넣어주면 된다. size 규칙도 만족한다.
만약 둘 다 min_pq.top 미만이라면, 둘 다 max_pq에 넣어줘야 한다. 이때, size 규칙 만족을 위해 위에서 했던 것처럼, max_pq.top을 빼서 min_pq에 
넣어준다.

이걸 해준 후, min_pq.top이 중앙값이므로 total에 더해준다. 그럼 끝.

이렇게 한다면, N번의 각 X, Y 입력에 대해서, 상수 번의 push/pop 연산을 하게 된다. push/pop 연산은 O(logN)이므로, O(N*logN)이니깐 시간복잡도 만족.
*/