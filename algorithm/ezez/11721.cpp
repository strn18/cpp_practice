#include <iostream>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string str;

  cin >> str;

  for(int i=0; i<str.size(); i++){
    cout << str[i];

    if(i%10 == 9) cout << '\n';
  }

  return 0;
}