#include <iostream>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string str[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
  int days[13] = {0, 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};
  int month, day, count = 0;

  cin >> month >> day;

  for(int i=1; i<=month; i++)
    count += days[i];
  count += day;

  cout << str[count%7];  

  return 0;
}