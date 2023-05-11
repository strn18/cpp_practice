#include <iostream>
#define MAX 100000

using namespace std;

long long one_to_n(long long n){
  return ((1+n)*n)/2;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  long long S, low, high, mid, sum_to_mid, max_N = 1;

  cin >> S;

  low = 1; high = MAX;
  while(low <= high){
    mid = (low+high)/2;
    sum_to_mid = one_to_n(mid);
    
    if(sum_to_mid == S){
      max_N = mid;
      break;
    }
    else if(sum_to_mid < S){
      max_N = mid;
      low = mid+1;
    }
    else high = mid-1;
  }

  cout << max_N;

  return 0;
}

/*
그냥 1씩 증가시키면서 하나하나 살펴봐도 되는데, 처음에는 S가 커지니까 프로그램이 먹통이 되길래 아니 시간 초과가 날리가 없는데? 싶어서 일단
시간 좀 줄여보려고 파라메트릭 서치로 풀었음. 근데 알고보니깐 one_to_n 함수에서 처음에는 매개변수로 int n을 받았는데, 그거 때문에 7행 연산에서
오버플로우가 나서 그랬음. 그래서 걍 다시 원래 방법대로 푼 게 1789-2.
*/