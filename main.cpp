#include <iostream>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int cur_sticks = 0, total = 0;
  char prev;
  string str;

  cin >> str;

  prev = str[0];

  for(int i=1; i<str.size(); i++){
    if(prev == '(' && str[i] == '('){
      cur_sticks++;
      total++;
    }
    else if(prev == '(' && str[i] == ')')
      total += cur_sticks;
    else if(prev == ')' && str[i] == ')')
      cur_sticks--;

    prev = str[i];
  }

  cout << total;

  return 0;
}