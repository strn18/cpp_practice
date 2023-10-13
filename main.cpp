#include <iostream>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string S;

  cin >> S;

  int length = S.size(), cur = 0, zeros = 0, ones = 0;

  S += "2";

  while(cur < length){
    if(S[cur] == '0'){
      zeros++;
      while(S[++cur] == '0') 1;
    }
    else{
      ones++;
      while(S[++cur] == '1') 1;
    }
  }

  cout << min(zeros, ones);

  return 0;
}