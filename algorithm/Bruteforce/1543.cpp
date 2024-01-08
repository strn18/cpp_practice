#include <iostream>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string target, word;

  getline(cin, target);
  getline(cin, word);

  int targetLen = target.size(), wordLen = word.length(), count = 0;

  for(int i=0; i<=targetLen - wordLen; i++){
    bool match = true;

    for(int j=0; j<wordLen; j++){
      if(target[i+j] != word[j]){
        match = false;
        break;
      }
    }

    if(match){
      count++;
      i += wordLen-1;
    }
  }

  cout << count;

  return 0;
}