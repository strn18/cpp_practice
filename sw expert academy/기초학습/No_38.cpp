// 촛불 이벤트(11. 이분탐색)
#include <iostream>
#define MAX 1414213562

using namespace std;

long long triangle(long long k);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    long long N;
    int ans = -1;

    cin >> N;

    long long low = 1, high = MAX;

    while(low <= high){
      long long mid = (low+high)/2;
      long long candle = triangle(mid);

      if(N < candle)
        high = mid-1;
      else if(N > candle)
        low = mid+1;
      else{
        ans = mid;
        break;
      }
    }

    cout << '#' << t << ' ' << ans << '\n';
  }

  return 0;
}

long long triangle(long long k){
  return (k*(k+1))/2;
}

/*
기초 이분탐색 문제. 주어지는 양초 개수 N이 최대 10^18인데, 이걸 갖고 K의 최댓값을 잘 구해보면 1414213562가 된다. 
(1,414,213,562 * 1,414,213,563 / 2 = 1,000,000,000,179,470,703 가 됨. 즉 10^18보다 처음으로 큰, 필요한 양초의 개수임)
이제 low = 1, high = 1414213562(MAX)로 시작해서, 이분탐색을 해주면 된다. 이때, 저 14억이라는 수를 더하고 곱하는 과정에서 int 범위를 넘어가게 
되므로, triangle 함수는 물론이고 low, high, mid를 모두 long long으로 설정하였다(low, high는 왜? 라고 할 수 있지만, 26행에서 두 수를 더하는 
과정에서 합이 28억이 넘어갈 수 있게 되는데, 두 수가 int라면 여기서 오버플로우 발생함). 그런 다음, mid단을 쌓기 위해 필요한 양초 개수인 candle과 
N을 비교하여, N이 작으면 high를 낮추고, 크면 low를 높이고, 같으면 답을 찾았으므로 break.
*/