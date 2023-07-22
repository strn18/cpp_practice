// 동아리실 관리하기(2. 비트연산)
#include <iostream>
#include <cstring>
#include <string>
#define MAX 10000
#define MOD 1000000007

using namespace std;

int dp[MAX][16]; // 0일부터 시작한다고 가정

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    int N, total = 0;
    string str;

    cin >> str;

    N = str.size();

    memset(dp, 0, sizeof(int)*(MAX)*16);

    for(int j=1; j<=15; j++){
      int temp = 1 << (str[0]-'A');

      if((j & 1) && (j & temp)) dp[0][j] = 1;
      else dp[0][j] = 0;
    }

    for(int i=1; i<N; i++){
      for(int j=1; j<=15; j++){
        int temp = 1 << (str[i]-'A');
        if((j & temp) == 0) dp[i][j] = 0;

        else{
          for(int k=1; k<=15; k++){
            if(j & k){
              dp[i][j] += dp[i-1][k];
              dp[i][j] %= MOD;
            }
          }
        }
      }
    }

    for(int j=1; j<=15; j++){
      total += dp[N-1][j];
      total %= MOD;
    }

    cout << '#' << t << ' ' << total << '\n';
  }

  return 0;
}

/*
https://g-idler.tistory.com/96 참고함.
*/