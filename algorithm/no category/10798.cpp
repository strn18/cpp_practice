#include <iostream>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string str[5];
  int maxLen = 0;

  for(int i=0; i<5; i++){
    cin >> str[i];

    if(maxLen < str[i].size()) maxLen = str[i].size();
  }

  for(int i=0; i<maxLen; i++){
    for(int j=0; j<5; j++){
      if(str[j].size() <= i) continue;

      cout << str[j][i];
    }
  }


  return 0;
}