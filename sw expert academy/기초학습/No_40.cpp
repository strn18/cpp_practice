// 광고 시간 정하기(11. 이분탐색)
#include <iostream>
#define MAX 100000

using namespace std;

int L, N;
int s[MAX], e[MAX];

bool check_peak(int k);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    cin >> L >> N;

    for(int i=0; i<N; i++)
      cin >> s[i] >> e[i];
    
    int ans = 0, low = 1, high = L;

    while(low <= high){
      int mid = (low+high)/2;

      if(check_peak(mid)){
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

bool check_peak(int k){
  int first = 0, last = 0;
  int peak_time = 0, total_time = 0;

  while(true){
    if(peak_time + (e[last]-s[last]) >= k){
      if(total_time + (k-peak_time) <= L) return true;
      else{
        peak_time -= (e[first]-s[first]);
        total_time -= (s[first+1]-s[first]);
        first++;
      }
    }
    else{
      if(last == N-1) return false;

      peak_time += (e[last]-s[last]);
      total_time += (s[last+1]-s[last]);
      last++;
    }
  }
}

/*
투 포인터 + 매개변수 탐색으로 풀었다. 
*/