#include <iostream>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string str;
  double grade;

  cin >> str;
  
  cout << fixed;
  cout.precision(1);

  if(str == "F"){
    cout << 0.0;

    return 0;
  }

  if(str[0] == 'A') grade = 4.0;
  else if(str[0] == 'B') grade = 3.0;
  else if(str[0] == 'C') grade = 2.0;
  else grade = 1.0;

  if(str[1] == '+') grade += 0.3;
  else if(str[1] == '-') grade -= 0.3;

  cout << grade;

  return 0;
}