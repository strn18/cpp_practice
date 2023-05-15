#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string str;

  while(true){
    getline(cin, str);

    if(str == ".") break;

    stack<char> st;
    bool flag = true;

    for(int i=0; i<str.size(); i++){
      if(str[i] == '(' || str[i] == '[')
        st.push(str[i]);

      else if(str[i] == ')'){
        if(!st.empty() && st.top() == '(') st.pop();
        else flag = false;
      }

      else if(str[i] == ']'){
        if(!st.empty() && st.top() == '[') st.pop();
        else flag = false;
      }
    }

    if(!st.empty()) flag = false;

    cout << (flag ? "yes" : "no") << '\n';
  }

  return 0;
}

/*
1. 처음에는 입력으로 한 줄만 들어오는 줄 알아서
2. 입력의 마지막이 EOF로 주어지는 줄 알아서
이 두 가지 때문에 계속 틀렸다.. 1번 때문에 입력을 한 줄(.이 주어질 때까지)만 받도록 해서 틀렸고, 2번 때문에 13행의 while문을
while(getline(cin, str)) 으로 했었음. 그래서 틀렸다. 
*/