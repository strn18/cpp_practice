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