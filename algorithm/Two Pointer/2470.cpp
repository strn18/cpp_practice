#include <iostream>
#include <algorithm>
#include <cstdlib>
#define MAX 100000
#define INF 2000000000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, val[MAX];
  int ans_val = INF, ans_left, ans_right;

  cin >> N;
  for(int i=0; i<N; i++)
    cin >> val[i];

  sort(val, val+N);

  int l = 0, r = N-1;  
  while(l < r){
    int sum = val[l]+val[r];

    if(abs(sum) < ans_val){
        ans_val = abs(sum);
        ans_left = l;
        ans_right = r;
        if(sum == 0) break;
    }

    if(sum < 0) l++;
    else r--;
  }

  cout << val[ans_left] << ' ' << val[ans_right];

  return 0;
}

/*
처음 풀어본 투 포인터 문제. 용액들을 오름차순으로 정렬해놓고, 맨 왼쪽에서 시작하는 l, 맨 오른쪽에서 시작하는 r을 투 포인터로 써서 풀면 된다.
처음에는, l++ 시켰을 때와 r-- 시켰을 때 중에서, 언제의 용액 합의 절댓값이 더 작은지?를 따져서, 더 작아지는 쪽으로 l or r을 움직였다. 그렇게 해서
제출하니 맞았음. 근데 https://ansohxxn.github.io/boj/2470/ 여기 풀이를 보니 더 깔끔해보여서 바꿨다.
현재 용액 합 값이 0보다 작으면? 값을 더 증가시켜야 0에 가까워지므로, l++ 해준다. 0보다 크면? 값을 더 감소시켜야 하므로, r-- 해주는 방식이다.
그리고 ans를 갱신해주는 시점이나 그런 게 더 깔끔해보여서 바꿨음. 제출하니 맞았다.
*/