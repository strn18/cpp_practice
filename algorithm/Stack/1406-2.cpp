#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string str;
  stack<char> left, right;
  int M;

  cin >> str;

  for(int i=0; i<str.size(); i++)
    left.push(str[i]);

  cin >> M;

  while(M--){
    char choice;

    cin >> choice;

    if(choice == 'L'){
      if(!left.empty()){
        right.push(left.top());
        left.pop();
      }
    }
    else if(choice == 'D'){
      if(!right.empty()){
        left.push(right.top());
        right.pop();
      }
    }
    else if(choice == 'B'){
      if(!left.empty()){
        left.pop();
      }
    }
    else{
      char ch;
      cin >> ch;
      left.push(ch);
    }
  }

  while(!left.empty()){
    right.push(left.top());
    left.pop();
  }

  while(!right.empty()){
    cout << right.top();
    right.pop();
  }

  return 0;
}

/*
링크드 리스트 말고 스택으로도 풀어봤다. 훨씬 쉬웠음.
*/