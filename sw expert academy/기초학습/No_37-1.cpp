// 영어 공부(11. 이분탐색)
#include <iostream>
#include <cstring>
#define MAX 1000000

using namespace std;

int n, p;

bool studied[MAX+1]; // studied[i]: i일에 실제로 공부했다면 true
int study_count[MAX+1]; // study_count[i]: 0일 ~ i일 중 실제로 공부한 날의 수

bool possible(int days); // days일만큼 공부 연속 기간이 가능하다면 true
int real_study(int start, int end); // start일 ~ end일 중 실제로 공부한 날의 수

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    cin >> n >> p;

    memset(studied, false, sizeof(bool)*(MAX+1));
    memset(study_count, 0, sizeof(int)*(MAX+1));

    for(int i=0; i<n; i++){
      int day;

      cin >> day;

      studied[day] = true;
      study_count[day] = 1;
    }

    for(int i=1; i<=MAX; i++)
      study_count[i] += study_count[i-1];

    int ans = 0, low = 2, high = n+p;

    while(low <= high){
      int mid = (low+high)/2;

      if(possible(mid)){
        ans = mid;
        low = mid+1;
      }
      else
        high = mid-1;
    }

    cout << '#' << t << ' ' << ans << '\n';
  }

  return 0;
}

bool possible(int days){
  for(int i=days-1; i<=MAX; i++)
    if(real_study(i-(days-1), i) + p >= days) return true;

  return false;
}

int real_study(int start, int end){
  if(start == 0) return study_count[end];
  else return study_count[end]-study_count[start-1];
}

/*
매개변수 탐색 + 누적합 개념 응용으로 푼 문제.

우선, 주어진 문제를 days일만큼의 공부 연속 기간이 가능한가? 로 바꾼다. 그런 다음, 가능한 days의 최댓값을 매개변수 탐색으로 구한다.
이를 위해 possible 함수를 정의했다. 역할은 위에서 말한 바와 같음. 가능하다면 true, or false를 리턴한다.

days일 동안 공부 연속 기간이 가능한지는 다음과 같이 찾았다. 만약, a일부터 b일까지 b-a+1일 동안, 실제로 공부를 한 날이 c일이라고 하자. 이때, 
c+p >= b-a+1 이라면? 실제로 공부를 한 c일 + 공부했다고 체크할 수 있는 p일을 합쳐서, b-a+1일 동안 연속으로 공부했다고 만들 수 있는 것이다. 

그렇기에 real_study 함수를 정의했다. start일 ~ end일 동안 실제로 공부한 날을 리턴하는 함수이다. 이를 63행에서 이용하였다. 
i-(days-1)일 ~ i일 동안 실제로 공부한 날 + p >= days 라면? 그 기간 동안 연속으로 공부했다고 만들 수 있으니 true를 리턴한다. 이를 가능한 
i에 대해 모두 해보고, 다 불가능할 경우 false를 리턴한다.

real_study 함수는 study_count 배열을 사용한다. study_count[i]는 0일 ~ i일 중 실제로 공부한 날의 수인데, 0일 ~ i일 중 실제로 공부한 날의 수는 
0일 ~ i-1일 중 실제로 공부한 날의 수 + (i일에 실제로 공부하였는가 ? 1 : 0) 이므로, 40행에서 채워주면 된다. 그런 다음, 부분합 느낌으로 
study_count를 이용하면 된다. start일 ~ end일 중 실제로 공부한 날의 수 = study_count[end] - study_count[start-1] 이다. 이때, start가 0인 
경우는 69행에서 예외처리 하였다.

다 풀고나서 여기저기 찾아봤는데, 투포인터로 풀 수 있다고 해서 풀어볼 예정.
*/