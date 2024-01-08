#include <iostream>
#include <cmath>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, count = 0; 
  
  cin >> N;

  for(int i=1; 1; i++){
    if(N < pow(10, i)){
      count += i * (N - pow(10, i-1) + 1);
      break;
    }
    else{
      count += i * (pow(10, i) - pow(10, i-1));
    }
  }

  cout << count;

  return 0;
}

/*
1) 1~9 => 9개
2) 10~99 => 90개
3) 100~999 => 900개
...
를 이용해서, N에서 1)에 해당하는 수의 개수를 세서 그 수 * 1을 count에 더하고, 2)에 해당하는 수의 개수를 세서 그 수 * 2을 count에 더하고... 
이렇게 풀었다. 
*/