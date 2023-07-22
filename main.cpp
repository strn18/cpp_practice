#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool is_alpha(char ch);
bool is_op(char ch);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string str;
  stack<char> op;

  cin >> str;

  for(int i=0; i<str.size(); i++){
    if(op.empty()){
      if(is_alpha(str[i])) cout << str[i];
      else if(is_op(str[i])) op.push(str[i]);
    }

    else if(op.top() == '+' || op.top() == '-'){
      if(is_alpha(str[i])) cout << str[i];
      else if(is_op(str[i])){
        if(str[i] == '*' || str[i] == '/') op.push(str[i]);
        else{
          if(str[i-2] != '('){
            cout << op.top();
            op.pop();
          }
          op.push(str[i]);
        }
      }
      else if(str[i] == ')'){
        cout << op.top();
        op.pop();
      }
    }

    else{
      if(is_alpha(str[i])){
        cout << str[i];

        if(str[i-1] != '('){
          cout << op.top();
          op.pop();
        }
      }
      else if(is_op(str[i])) op.push(str[i]);
    }
  }

  while(!op.empty()){
    cout << op.top();
    op.pop();
  }

  return 0;
}

bool is_alpha(char ch){
  if('A' <= ch && ch <= 'Z') return true;
  else return false;
}

bool is_op(char ch){
  if(ch == '+' || ch == '-' || ch == '*' || ch == '/') return true;
  else return false;
}