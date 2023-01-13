#include <iostream>
#define INF 2147483647

using namespace std;

int mat[500][2];
int dp[500][500] = {0};

int DP(int i, int j);

int main(){
  int N, r, c;

  scanf("%d", &N);
  for(int i=0; i<N; i++){
    scanf("%d %d", &r, &c);
    mat[i][0] = r;
    mat[i][1] = c;
  }

  printf("%d", DP(0, N-1));

  return 0;
}

int DP(int i, int j){
  if(!dp[i][j]){
    if(i != j){
      dp[i][j] = INF;
      for(int k=1; k<=j-i; k++){
        dp[i][j] = min(dp[i][j], DP(i, j-k)+DP(j-k+1, j) + mat[i][0]*mat[j-k][1]*mat[j][1]);
      }
    }
  }
  return dp[i][j];
}

/*
11066과 거의 유사했던 dp문제. 처음에는 좀 고민했으나, 크게 어렵진 않았다. dp[i][j]: i번 행렬부터 j번 행렬까지 곱할 때 필요한 곱셈 연산의 최솟값.
이라고 두고, dp[i][j] = min(dp[i][j-k]+dp[j-k+1][j]+mat[i][0]*mat[j-k][1]*mat[j][1]), k는 [1, j-i]. 라는 점화식을 세우며 어렵지 않게 풀었다.

i번 행렬부터 j번 행렬까지 곱할 때 필요한 곱셈 연산의 최솟값은, 그 사이 행렬들을 두 부분으로 나눴을 때, '왼쪽 부분을 곱할 때 필요한 곱셈 연산의
최솟값' + '오른쪽 부분을 곱할 때 필요한 곱셈 연산의 최솟값' + '왼쪽 부분을 곱해서 나온 행렬과 오른쪽 부분을 곱해서 나온 행렬을 곱할 때 필요한
곱셈 연산'과 같다. 그렇기 때문에, k라는 변수를 하나 더 만들어서 왼쪽 부분과 오른쪽 부분을 조정해나가며 각 부분의 DP값과 두 부분을 곱할 때의 
곱셈 연산(mat끼리 곱하는 부분)의 합의 최소를 구해주면 된다. dp값을 아직 안 구했다는 것(not visited)을 dp값이 0인지 아닌지로 판단했는데, 이때
i==j 일 때는 dp값이 0인게 맞기 때문에 DP 함수 내에서 if(i != j)를 통해 i==j일 때는 연산을 하지 않고 그대로 0으로 두도록 예외 처리를 해주었다.
*/