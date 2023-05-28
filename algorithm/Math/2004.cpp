#include <iostream>
#include <cmath>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;

  cin >> n >> m;

  int count2 = 0, count5 = 0;

  for(int i=1; pow(2, i)<=n; i++){
    int cur = pow(2, i);
    count2 += (n/cur) - ((n-m)/cur);
  }

  for(int i=1; pow(5, i)<=n; i++){
    int cur = pow(5, i);
    count5 += (n/cur) - ((n-m)/cur);
  }

  for(int i=1; pow(2, i)<=m; i++){
    int cur = pow(2, i);
    count2 -= (m/cur);
  }

  for(int i=1; pow(5, i)<=m; i++){
    int cur = pow(5, i);
    count5 -= (m/cur);
  }

  cout << min(count2, count5);

  return 0;
}

/*
처음에 좀 헤맸던 문제. nCm 관련 문제인데, n과 m이 최대 20억까지라서 콤비네이션 쓸 때 주로 풀던 dp 방식(nCm = n-1Cm + n-1Cm-1 점화식)로도 
풀 수 없음. 그래서 좀 다르게 생각해봤는데, 어차피 맨 끝의 0의 개수만 출력하면 되니까, 10이 얼마나 곱해져있는지가 중요한 게 아닐까? 라는 생각을
했음. 가령 nCm을 소수의 제곱꼴의 합으로 표현했을 때 nCm = 2^3 + 3^? + 5^4 + 7^? + ... 라면, nCm에는 10이 총 3번 곱해져 있는 거니까, 맨 끝의
0은 3개일 것이다. 이를 이용하여, nCm에 2가 a번, 5가 b번 곱해져있다고 하면, 답은 min(a, b)가 된다. 

이를 구하기 위해, 8C4 = 8 7 6 5 / 4 3 2 1 이렇게 되는 것을 이용하여, 분모에 2와 5가 곱해져있는 횟수에 분자의 그 횟수를 빼줘서 구하기로 했음.
우선 분모에 2, 4, 8, ... 등 2의 제곱수가 몇 번 곱해져있는지를 다 구하면 2가 곱해져있는 총 횟수를 구할 수 있고, 5도 마찬가지로 5, 25, ... 를 
구하면 된다. 이 부분이 16행과 21행. 그리고 분자도 마찬가지로 26행과 31행에서 구해줌. 

써놓고 보니까 좀 어렵게 푼 것 같은데, https://j3sung.tistory.com/235 여기랑 비슷한 맥락이다.
*/