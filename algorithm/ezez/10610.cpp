#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string num;
  int sum = 0;

  cin >> num;

  sort(num.begin(), num.end(), greater<>());

  for(int i=0; i<num.size(); i++)
    sum += num[i]-'0';

  if(num.back() != '0' || sum%3 != 0) cout << -1;
  else cout << num;
  
  return 0;
}

/*
문자열 써서 쉽게 풀 수 있는 문제. 어떤 수가 30의 배수이려면, 3의 배수 * 10 이면 되니까,
1) 수가 0으로 끝난다 2) 각 자릿수의 합이 3의 배수이다
이 두 개를 만족하면 됨. 그러므로, 이 두 조건을 만족하는지는 21행에서 검사해주고, 이게 맞다면 가장 큰 수를 만들고 싶은 거니까 각 자릿수를 내림차순
정렬해서 출력하면 된다.
*/