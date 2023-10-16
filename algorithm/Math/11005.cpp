#include <iostream>

using namespace std;

char convert(long long n);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  long long N, B, num = 1;

  cin >> N >> B;

  while((N / num) > 0) num *= B;
  
  num /= B;

  while(num > 0){
    cout << convert(N / num);
    N %= num;
    num /= B;
  }

  return 0;
}

char convert(long long n){
  if(n < 10) return '0' + n;
  else return 'A' + (n - 10);
}

/*
진법의 기본 개념 쓰는 문제. https://minyeok2ee.gitlab.io/boj/boj-11005/ 좀 더 쉬운 버전. 
*/
