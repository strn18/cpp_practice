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

/*
연속한 0 덩어리들의 개수와 연속한 1 덩어리들의 개수 중 작은 값이 답이다. 
나는 S[cur]에서 0 or 1을 발견하면, zeros++ or ones++ 을 해주고, 1 or 0을 발견할 때까지 cur++을 해주는 방식을 썼다. 
근데 다른 풀이 보니까, S[i] != S[i+1] 이면 zeros++ or ones++ 을 해주는 더 쉬운 방식도 있었다. 
*/