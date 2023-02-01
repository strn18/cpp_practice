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