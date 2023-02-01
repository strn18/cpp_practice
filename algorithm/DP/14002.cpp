#include <iostream>
#include <stack>
#define MAX 1000

using namespace std;

int main(){
  int N, max_idx, max_len = 0;
  int num[MAX], dp[MAX], prev_idx[MAX];
  stack<int> st;

  scanf("%d", &N);

  for(int i=0; i<N; i++){
    int max_dp = 0;
    prev_idx[i] = -1;

    scanf("%d", &num[i]);

    for(int j=0; j<i; j++){
      if(num[j] < num[i] && dp[j] > max_dp){
        max_dp = dp[j];
        prev_idx[i] = j;
      }
    }

    dp[i] = max_dp+1;

    if(dp[i] > max_len){
      max_len = dp[i];
      max_idx = i;
    }
  }

  st.push(num[max_idx]);
  while(prev_idx[max_idx] != -1){
    st.push(num[prev_idx[max_idx]]);
    max_idx = prev_idx[max_idx];
  }

  printf("%d\n", max_len);

  while(!st.empty()){
    printf("%d ", st.top());
    st.pop();
  }

  return 0;
}

/*
어렵지 않았던 dp문제. 11053과 거의 비슷한데, 그거는 길이를 구하는 문제였고 이번에는 수열 자체를 구하면 된다.

우선 dp[i]: i번째 수를 고를 때, 가장 긴 증가하는 부분 수열(LIS)의 길이. 라고 두면, dp[i]를 구하기 위해서는 j가 [0, i)일 때 dp[j]를 본다.
num[j] < num[i]를 만족할 때, dp[j]가 최댓값인 j를 찾으면, dp[i] = dp[j]+1이 된다. 왜냐? num[i]보다 앞에 있는 수 중에서, num[i]보다 작은
수들을 찾고(num[i]를 골라야하는데, 증가하는 수열이어야 하니까), 그 중에서 dp[j] 값이 최대인, 즉 num[j]까지의 증가하는 부분 수열이 가장 길
때를 찾고, 거기 뒤에다가 num[i]를 붙여주면 된다. 그리고 그 때의 수열의 길이가 dp[i]가 된다.

그 다음은 수열을 출력하면 되는데, 처음에는 dp[0]~dp[N-1]을 돌면서 dp가 1일 때 num값 출력하고, 그 다음은 2일 때 출력하고... 하는 방식으로
했는데, 그러면 반례가 생긴다. 주어진 수열이 9 4 6 8 일 경우, 답은 4 6 8 인데, 9 6 8 을 출력해버림..
그래서, prev_idx 배열을 만들었다. prev_idx[i]: i번째 수를 골라 LIS를 만들었을 때 i번째 수 바로 앞에 오는 수의 인덱스. 를 뜻한다.
이렇게 한 다음, 끝에서부터 하나하나 찾으면서 스택에 넣고, 출력할 때는 반대로 빼주었다(스택이니깐).

https://tjdahr25.tistory.com/20 여기 글 상단을 보니까, LIS 길이를 O(NlogN)으로 구하는 법도 있었음.
*/