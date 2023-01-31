// https://gusdnr69.tistory.com/146
// https://allmymight.tistory.com/m/85
#include <iostream>
#include <string>

using namespace std;

long long dp[101][101][101] = {0};

long long DP(int n, int m, int x);
long long Combination(int n, int m);

int main(){
  int N, M, K;
  string ans = "";

  scanf("%d %d %d", &N, &M, &K);

  while(K != 1){
    bool flag = false;

    for(int i=0; i<=N; i++){
      if(DP(N, M, i+1) > K){
        flag = true;

        K -= (DP(N, M, i)-1);

        for(int j=0; j<N-i; j++)
          ans += "a";
        N = i;

        ans += "z";
        M--;

        break;
      }
    }

    if(!flag){
      printf("-1");
      return 0;
    }
  }

  for(int i=0; i<N; i++)
    ans += "a";
  for(int i=0; i<M; i++)
    ans += "z";

  cout << ans;
  
  return 0;
}

long long DP(int n, int m, int x){
  if(dp[n][m][x]) return dp[n][m][x];

  if(x <= 1){
    dp[n][m][x] = x+1;
    return dp[n][m][x];
  }

  if(x == n+1){ // 요기랑 21행 연관
    dp[n][m][x] = Combination(n+m, n) + 1;
    return dp[n][m][x];
  }

  dp[n][m][x] += DP(n, m, x-1);
  for(int i=m-1; i>0; i--){
    dp[n][m][x] += (DP(x-1, i, x-1) - 1);
  }
  dp[n][m][x] += 1;

  return dp[n][m][x];
}

long long Combination(int n, int m){
  int ori_m = m;
  long long result = 1; // 요기

  for(int i=0; i<ori_m; i++)
    result *= n--;
  for(int i=0; i<ori_m; i++)
    result /= m--;

  return result;
}

/*
존나 빢셌던 dp문제. 문제 자체는 간단한데, N개의 a와 M개의 z를 통해 문자열을 만들 때, 사전 순으로 K번째(1based 기준)의 문자열을 구하면 된다.
근데 많이 어려웠다. 이리저리 고민하다가 한 가지 방법을 떠올림.

예를 들어 a가 3개 있고 z가 2개 있을 때, 1번째 문자열은 aaazz이다. 이때 맨 왼쪽의 z를 왼쪽으로 한 칸 옮긴 거는 aazaz이고, 두 칸 옮긴 거는 
azaaz이고, 세 칸은 zaaaz이다. 여기서, 맨 왼쪽의 z를 몇 칸 옮긴 것이, 몇 번째 문자열인지 안다면? 
즉 한 칸 옮긴 거는 1번째, 두 칸은 4번째, 세 칸은 7번째라는 걸 안다고 해보자. 이때 주어진 K가 5라면, aaazz를 시작으로 5번째 문자열을 구하는
건데, 맨 왼쪽 z를 두 칸 옮긴게 4번째니까, 5번째 문자열은 "az" + "aaz"를 시작으로 2번째 문자열 일 것임.
이걸 반복하다보면 구할 수 있지 않을까? 라는 생각이었다.

dp[n][m][x] = value: a가 n개, z가 m개 있을 때, 좌측 z를 왼쪽으로 x칸 옮긴 문자열은 value번째 문자열이다. 로 정의했다.
그 다음, value값이 K보다 크지 않을 때 최댓값을 찾고(21행), (value-1)을 K에서 빼준다. 왜 1을 뺀 값을 빼주는지는 위의 예시를 보면 알 수 있음.
그런 다음, 원래 a가 N개 있었을텐데 맨 왼쪽 z를 왼쪽으로 i칸 옮겼으니 N-i개의 a가 그 z의 왼쪽에 위치하게 된다. 그러므로 26행에서 ans에 
더해준다. 그리고 원래 N개 있던 a 중에서 방금 말한 N-i개의 a가 왼쪽에 고정됐으니깐, 우측에는 i개의 a가 남는다. 그래서 a의 개수를 i로 갱신.
그리고 왼쪽으로 옮긴 z를 ans에 더해주고, 개수 하나 줄었으니 M--를 해준다. 

아 근데 풀이 쓰다보니까 현타온다 내가 푼 건데도 설명하기 너무 어렵다.. 다른 사람들 풀이보니까 확실히 쉬워보임.

dp 점화식 설명하자면, 예를 들어 dp[3][4][3]을 알고 싶다고 치자. 그러면, aaazzzz에서 좌측 z를 왼쪽으로 세 칸 옮긴 zaaazzz가 몇 번째인지 알고
싶은 거임. 근데 그 문자열은, 모든 z를 좌측으로 두 칸 옮긴 azzzzaa의 바로 다음 문자열이다. 즉, 우선 aaazzzz에서 1번째 z를 좌측으로 두 칸 옮기고,
그 결과인 azaazzz에서 aazzz만 봤을 때, 거기서 또 1번째 z를 좌측으로 두 칸 옮기고, 그 결과인 zaazz에서 aazz만 봤을 때, 거기서 또 1번째 z를
좌측 두 칸 옮기고, 그 결과인 zaaz에서 aaz만 봤을 때, 거기서 또 1번째 z를 좌측 두 칸 옮기면 그 결과는 zaa가 되겠지? 
이거 다 합치면 결국 azzzzaa가 된다. 
즉, dp[n][m][x]를 알고 싶다면, 우선 dp[n][m][x-1]을 더해준다(66행). 그런 다음 오른쪽을 쪼개가면서 더해주면 됨.. 설명하기 ㅈㄴ 어렵네
70행에서 1 더해주는 건, 106행에서 말했다시피 알고 싶은 건 azzzzaa의 바로 다음 문자열이 몇 번째인지? 이니까 1 더해줘야 하는 거다.

걍 예시를 들어서 생각하는게 이해하기 편할 것..
*/