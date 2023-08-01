// 영어 공부(11. 이분탐색)
#include <iostream>
#include <cstring>
#define MAX 1000000

using namespace std;

bool studied[MAX+1];

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    int n, p, last_day;

    cin >> n >> p;

    memset(studied, false, sizeof(bool)*(MAX+1));

    for(int i=0; i<n; i++){
      cin >> last_day;
      studied[last_day] = true;
    }

    int ans = 0, start = 0, end = 0;

    if(!studied[0]) p--;

    last_day = min(last_day + p, MAX);

    while(end <= last_day){
      if(p >= 0){
        ans = max(ans, end-start+1);
        end++;
        if(!studied[end]) p--;
      }
      else{
        if(!studied[start]) p++;
        start++;
      }
    }

    cout << '#' << t << ' ' << ans << '\n';
  }

  return 0;
}

/*
투포인터로 풀었다. start와 end를 잡고, 만약 start일 ~ end일을 연속 공부 기간으로 할 수 있다면(36행) ans를 갱신하고 end++을 해준다. 이때, 
end일에 실제로 공부를 안 했다면, 체크해야 하는 날이 하루 늘어나므로 p--를 해준다. 만약 start일 ~ end일을 연속 공부 기간으로 할 수 없다면(41행), 
start++을 해준다. 그 전에, start일에 실제로 공부를 안 했다면, 이제 체크해야 하는 날이 하루 줄어드므로 p++을 해준다.

이것을 end <= last_day일 때 반복한다. last_day는, 실제로 공부를 한 마지막 날 + p 이다. 마지막 날 다음 날부터 p일을 다 체크하고 나면, 그 이후로는 
어차피 볼 필요 없다. 이때, 이 값이 MAX를 넘어가지 않도록 33행과 같이 연산해준다.
*/