#include <iostream>
#include <string>

using namespace std;

string S;

void print(int start, int end, bool rev);
bool isAlphaNum(char ch);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  bool isWord = false, isTag = false;
  int start = 0;

  getline(cin, S);

  for(int i=0; i<S.size(); i++){
    if(isTag){
      if(S[i] == '>'){
        print(start, i, false);
        isTag = false;
      }
    }

    else if(isWord){
      if(!isAlphaNum(S[i])){
        print(start, i-1, true);
        isWord = false;

        if(S[i] == '<'){
          start = i;
          isTag = true;
        }
        else cout << ' ';
      }
    }

    else{
      if(isAlphaNum(S[i])){
        isWord = true;
        start = i;
      }
      else{
        isTag = true;
        start = i;
      }
    }
  }

  if(isWord) print(start, S.size()-1, true);
  
  return 0;
}

void print(int start, int end, bool rev){
  if(rev){
    for(int i=end; i>=start; i--)
      cout << S[i];
  }
  else{
    for(int i=start; i<=end; i++)
      cout << S[i];
  }
}

bool isAlphaNum(char ch){
  if(ch == ' ' || ch == '<' || ch == '>') return false;
  else return true;
}