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

/*
우선 알파벳이 등장한 횟수를 센다. 만약 홀수로 등장한 횟수의 알파벳이 2개 이상인 경우 팰린드롬을 만들 수 없으므로 25행에서 예외처리.
만약 해당 알파벳이 1개일 경우, 그 인덱스(0~25)를 oddIdx에 담는다. 그 다음, A부터 차례대로 등장 횟수의 반만큼을 출력해주고, 
홀수 등장 횟수 알파벳이 있으면 oddIdx로 그걸 한 개 출력해준 후, 다시 반대로 Z부터 차례대로 등장 횟수의 반만큼을 출력해준다.

https://code-kh-studio.tistory.com/9 여기를 보니까, 반만큼 문자열을 만들어두고 반대로 뒤집은 다음, 홀수 등장 횟수 알파벳 
하나와 반대로 뒤집은 걸 뒤에 차례대로 붙여주는 방법이었다.
*/