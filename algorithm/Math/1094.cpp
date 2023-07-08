#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int X, total_len = 64, min_len = 64, count = 1;
  
  cin >> X;

  while(total_len != X){
    min_len /= 2;
    count++;

    if(total_len - min_len >= X){
      total_len -= min_len;
      count--;
    }
  }

  cout << count;

  return 0;
}
/*
그냥 하나하나 자르는 방식으로 풀긴 했는데, https://scarlettb.tistory.com/62 여기처럼 직접 계산해서 푸는 방법도 있음.
*/