#include <iostream>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int N;
  string pattern;

  cin >> N;

  cin >> pattern;

  for(int i=1; i<N; i++){
    string str;

    cin >> str;

    for(int j=0; j<pattern.size(); j++)
      if(pattern[j] != str[j]) pattern[j] = '?';
  }

  cout << pattern;

  return 0;
}