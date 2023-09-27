#include <iostream>
#include <string>
#define SRY "I'm Sorry Hansoo"

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string str;
  int count[26] = {0};

  cin >> str;

  for(int i=0; i<str.size(); i++)
    count[str[i]-'A']++;
  
  int oddAllow = (str.size()%2 == 0 ? 0 : 1);
  int oddIdx = -1;

  for(int i=0; i<26; i++){
    if(count[i]%2 == 1){
      if(oddAllow == 0){
        cout << SRY;
        return 0;
      }
      else{
        oddAllow--;
        oddIdx = i;
      }
    }
  }

  for(int i=0; i<26; i++)
    for(int j=0; j<count[i]/2; j++)
      cout << (char)('A' + i);
  
  if(oddIdx != -1) cout << (char)('A' + oddIdx);

  for(int i=26; i>=0; i--)
    for(int j=0; j<count[i]/2; j++)
      cout << (char)('A' + i);

  return 0;
}