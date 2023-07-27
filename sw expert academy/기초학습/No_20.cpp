// 최장 공통 부분 수열(6. DP)
#include <iostream>
#include <string>
#define MAX 1000

using namespace std;

int dp[MAX+1][MAX+1] = {0};

int main(){
  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    string A, B;

    cin >> A >> B;

    for(int i=1; i<=A.size(); i++){
      for(int j=1; j<=B.size(); j++){
        if(A[i-1] == B[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
        else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
      }
    }
    
    cout << '#' << t << ' ' << dp[A.size()][B.size()] << '\n';
  }

  return 0;
}

/*
걍 기초 LCS 문제.
*/