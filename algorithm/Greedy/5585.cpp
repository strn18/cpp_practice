#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int money, count = 0;
  int change[6] = {500, 100, 50, 10, 5, 1};

  cin >> money;
  money = 1000 - money;

  for(int i=0; i<6; i++){
    int n = (money/change[i]);
    money -= n*change[i];
    count += n;
  }

  cout << count;
  
  return 0;
}