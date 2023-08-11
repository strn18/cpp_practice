#include <iostream>
#include <string>
#include <list>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  while(T--){
    string str;
    list<char> pw;
    list<char>::iterator cur = pw.end();

    cin >> str;

    for(auto ch: str){
      if(ch == '<'){
        if(cur != pw.begin()) cur--;
      }
      else if(ch == '>'){
        if(cur != pw.end()) cur++;
      }
      else if(ch == '-'){
        if(cur != pw.begin()){
          cur--;
          cur = pw.erase(cur);
        }
      }
      else{
        pw.insert(cur, ch);
      }
    }

    for(auto ch: pw)
      cout << ch;
    
    cout << '\n';
  }

  return 0;
}

/*
1406-3이랑 거의 비슷하게 푼 문제.
*/