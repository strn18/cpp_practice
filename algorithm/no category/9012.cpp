#include <iostream>

using namespace std;

bool VPS(string str);

int main(){
  int T;
  scanf("%d", &T);

  while(T--){
    string str;
    cin >> str;
    if(VPS(str))
      cout << "YES\n";
    else
      cout << "NO\n";
  }

  return 0;
}

bool VPS(string str){
  int start = 0, end = 0;
  
  for(int i=0; str[i]!=0; i++){
    if(str[i]=='(')
      start++;
    else
      end++;
    if(end > start)
      return false;
  }
  if(start != end)
    return false;

  return true;
}

/*
시간 없어서 간단하게 풀어본 문제. 그냥 문자열의 왼쪽부터 '('와 ')'의 개수를 세어가면서, ')'의 개수가 더 많아졌다면 false를 리턴하면 된다. 그리고
탐색이 다 끝났을 때 둘의 개수가 같다면 true를 리턴한다.
*/