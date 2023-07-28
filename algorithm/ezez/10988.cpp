#include <iostream>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string str;
  bool is_palin = true;

  cin >> str;

  int size = str.size();

  for(int i=0; i<size/2; i++){
    if(str[i] != str[size-1-i]){
      is_palin = false;
      break;
    }
  }

  cout << (is_palin ? 1 : 0);

  return 0;
}