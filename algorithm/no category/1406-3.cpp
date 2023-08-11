#include <iostream>
#include <list>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  list<char> li;
  string str;
  int M;

  cin >> str;

  for(int i=0; i<str.size(); i++)
    li.push_back(str[i]);

  list<char>::iterator cur = li.end();
  
  cin >> M;

  while(M--){
    char cmd;

    cin >> cmd;

    if(cmd == 'L'){
      if(cur != li.begin()) cur--;
    }
    else if(cmd == 'D'){
      if(cur != li.end()) cur++;
    }
    else if(cmd == 'B'){
      if(cur != li.begin()){
        cur--;
        cur = li.erase(cur);
      }
    }
    else{
      char ch;
      cin >> ch;
      li.insert(cur, ch);
    }
  }

  for(auto c: li)
    cout << c;

  return 0;
}

/*
1406-1에서는 링크드 리스트를 직접 구현해서 풀었는데, 이번엔 list STL을 사용해서 풀었다. 
*/