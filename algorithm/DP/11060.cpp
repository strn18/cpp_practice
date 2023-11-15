#include <iostream>
#define MAX 1000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, A[MAX], dp[MAX];

  cin >> N;

  for(int i=0; i<N; i++){
    cin >> A[i];
    dp[i] = MAX;
  }
  
  dp[0] = 0;

  for(int i=0; i<N-1; i++){
    for(int j=1; j<=A[i]; j++){
      if(i + j < N) dp[i + j] = min(dp[i + j], dp[i] + 1);
    }
  }

  cout << (dp[N-1] == MAX ? -1 : dp[N-1]);

  return 0;
}

/*
dp[i]: i칸으로 올 수 있는 최소 step의 값. 1000일 경우 올 수 없음을 의미. 
*/