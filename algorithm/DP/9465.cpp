#include <iostream>
#include <algorithm>

using namespace std;

int main(){
  int T;

  scanf("%d", &T);
  while(T--){
    int n;
    int s[100000][2], dp[100000][2];

    scanf("%d", &n);
    for(int j=0; j<2; j++)
      for(int i=0; i<n; i++)
        scanf("%d", &s[i][j]);
  
    for(int i=0; i<n; i++){
      if(i>=2){
        dp[i][0] = max({dp[i-2][0], dp[i-2][1], dp[i-1][1]})+s[i][0];
        dp[i][1] = max({dp[i-2][0], dp[i-2][1], dp[i-1][0]})+s[i][1];
      }
      else if(i==1){
        dp[i][0] = dp[i-1][1]+s[i][0];
        dp[i][1] = dp[i-1][0]+s[i][1];
      }
      else{
        dp[i][0] = s[i][0];
        dp[i][1] = s[i][1];
      }
    }
    printf("%d\n", max(dp[n-1][0], dp[n-1][1]));
  }

  return 0;
}

/*
어렵지 않았던 dp문제. 다만 21~22행 점화식 부분에서, 21행의 dp[i-2][0] 부분과 22행의 dp[i-2][1] 부분은 빼도 된다(불필요한 비교). 왜냐하면, 
21행의 dp[i-2][0]보다 dp[i-1][1]이 반드시 크고(dp[i-2][0]이 아무리 커봤자, 어차피 [i-1][1]은 고를 수 있으니 dp[i-1][1]이 적어도 c[i-1][1]
만큼은 크다), 마찬가지로 22행의 dp[i-2][1]보다 dp[i-1][0]이 반드시 크기 때문에, 두 부분은 빼도 된다.
빼고 제출한 결과 맞았음
*/