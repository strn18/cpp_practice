// 스팟마트
#include <iostream>
#include <algorithm>
#include <cstring>
#define MAX_N 3001
#define MAX_M 101

using namespace std;

int N, M;
int A[MAX_N], B[MAX_M];
int dp[MAX_N][MAX_M][MAX_M][2];

int DP(int nCur, int mPicked, int mPassed, int prevPicked);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    cin >> N;

    for(int i=0; i<N; i++)
      cin >> A[i];
    
    cin >> M;

    for(int i=0; i<M; i++)
      cin >> B[i];
    
    memset(dp, -1, sizeof(dp));

    sort(B, B+M, greater<int>());

    cout << '#' << t << ' ' << DP(0, 0, 0, 0) << '\n';
  }

  return 0;
}

int DP(int nCur, int mPicked, int mPassed, int prevPicked){
  if(dp[nCur][mPicked][mPassed][prevPicked] != -1) return dp[nCur][mPicked][mPassed][prevPicked];

  int ret = 0;

  if(prevPicked){
    if(nCur < N) ret = max(ret, DP(nCur + 1, mPicked, mPassed, 0));
    if(mPicked + mPassed < M) ret = max(ret, DP(nCur, mPicked, mPassed + 1, 0));
  }
  else{
    if(nCur < N){
      ret = max(ret, DP(nCur + 1, mPicked, mPassed, 1) + A[nCur]);
      ret = max(ret, DP(nCur + 1, mPicked, mPassed, 0));
    }
    if(mPicked + mPassed < M){
      ret = max(ret, DP(nCur, mPicked + 1, mPassed, 1) + B[mPicked]);
      // ret = max(ret, DP(nCur, mPicked, mPassed + 1, 0));
    }
  }

  return dp[nCur][mPicked][mPassed][prevPicked] = ret;
}

/*
아무리 고민해봐도 모르겠어서 찾아봤다. https://suhwanc.tistory.com/193 여기를 참고함.

읽어봐도 처음엔 잘 이해가 안 갔음. 근데 보다보니 좀 이해가 갔다. 
DP(int nCur, int mPicked, int mPassed, int prevPicked)는 다음의 뜻을 가진다. 
현재 A[nCur] 과자를 보고 있고(0-based index 사용), mPicked개의 B를 골랐고 mPassed개의 B를 패스했다. 이때 패스란? 어떠한 자리에 
B를 넣긴 했는데, 고르지 않고 지나갔다는 뜻임. 그리고 prevPicked(0 or 1)는 직전 과자(A 또는 B겠지)를 골랐는지 안 골랐는지를 의미한다. 

만약 직전 과자를 골랐다면? 지금 보고 있는 위치인 A[nCur] 과자 왼쪽에 있는 과자를 골랐다는 것이다. 이때, A[nCur]를 고르거나, 또는 그 왼쪽에 
B 과자를 넣어서 그걸 고를 순 없으므로(연속 고르기 불가), 반드시 A or B 과자를 패스하도록 해야 한다. 50행이 A[nCur] 과자를 안 고르고 
패스했다는 뜻이고, 51행이 그 왼쪽(직전에 고른 과자와 A[nCur] 사이)에 B 과자를 집어 넣고 그걸 패스하게 했다는 뜻이다. 

만약 직전 과자를 안 골랐다면? 지금 보고 있는 A[nCur] 과자를 고를 수도 있고, 그 왼쪽에 B 과자를 넣어서 고를 수도 있고, 또는 다시 한 번 
패스할 수도 있다. 55행이 A[nCur] 과자를 고른 것이다. 56행은 A[nCur] 과자도 패스한 것이다. 59행은 직전에 안 고른 과자와 A[nCur] 사이에 
B 과자를 집어 넣고 그걸 고른 것이다. 60행은 집어 넣고 그걸 패스한 것이다. 그런데 이떄!! 60행은 볼 필요가 없다. 왜냐? 직전 과자를 이미 안 
고른 상태라, 다음 과자를 고를 수 있는 상태인데, 이때 굳이 B 과자를 또 집어넣고 그것도 패스할 필요가 없음. 어라 그럼 56행은 왜 필요한데요? 
가령 A = {5, 1, 1, 5}, B = {} 라고 하자. 이 상태라면, A[0]을 고르고, A[1]을 패스하고, A[2]도 패스해야 A[3]을 골라 최적의 선택을 할 수 
있다. 그래서 56행은 필요함(패스 두 번). 

또 여기서 중요한 점으로, B를 내림차순 정렬을 해놔야 한다. 그런 다음, B를 넣어 그걸 고를 때는 왼쪽(앞)의 원소부터, B를 넣어 그걸 패스할 
때는 오른쪽의 원소부터 넣어야 한다. 뭔 소리냐? B = {3, 1, 4, 5}라면, 이를 정렬하여 {5, 4, 3, 1}로 만든다. 그런 다음, B를 넣어 그걸 
고를 때는? 우선 값이 큰 걸 골라야 하니까 5를 넣는다. 그리고 B를 넣어 그걸 패스할 때는? 반대로 값이 적은 걸 패스해야 최적이니까 1을 넣어 
패스한다. B를 넣어 그걸 골랐다면 mPicked를, 패스했다면 mPassed를 +1 해주면 되는 것임. 

그리고 nCur == N이 되었다면, 마지막 과자(A[N-1])의 오른쪽 빈 공간을 보고 있는 것이다. 이때 A 과자를 더 고른다든가 할 수는 없음!
mPicked + mPassed == M이 되었다면, B 과자를 모두 넣어서 골랐거나 패스시켰다는 것이다. 이때 B 과자를 더 넣어서 고르거나 패스시킬 수 없음!

이렇게 다 짰는데, -1로 초기화 하는 부분을 잘못해서 자꾸 틀림. 원래 for문으로 초기화했었는데, dp[i][j][k][0], dp[i][j][k][1]에 대해서, 
i = [0, N], j, K = [0, M]에 대해서 다 -1을 넣어줘야 하는데 각각 [0, N), [0, M)에 대해서만 넣는 바람에 틀렸음.

고치고 제출했는데 시간초과 남. 링크의 코드랑 비교하니 memset 부분만 달라서 혹시? 하고 for문이 아니라 memset으로 초기화하도록 했더니 
맞았다.
*/