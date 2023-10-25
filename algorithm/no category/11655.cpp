#include <iostream>
#include <string>

using namespace std;

bool isAlpha(char ch){
  if('a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z') return true;
  else return false;
}

int main(){
  // ios_base::sync_with_stdio(false);
  // cin.tie(NULL);

  string str;

  getline(cin, str);

  for(auto ch: str){
    if(!isAlpha(ch)) printf("%c", ch);
    else if('a' <= ch && ch <= 'm' || 'A' <= ch && ch <= 'M') printf("%c", ch + 13);
    else printf("%c", ch - 13);
  }

  return 0;
}