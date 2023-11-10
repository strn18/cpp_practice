#include <iostream>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string str;
  int total = 10;

  cin >> str;

  for(int i=1; i<str.size(); i++){
    if(str[i] != str[i-1]) total += 10;
    else total += 5;
  }

  cout << total;

  return 0;
}