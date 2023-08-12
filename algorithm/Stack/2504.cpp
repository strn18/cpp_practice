#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string str;

  stack<pair<int, int>> st;
  int depth = 0;

  stack<char> check;
  bool avail = true;

  cin >> str;

  for(auto ch: str){ // 우선 주어진 괄호열이 유효한지 확인.
    if(ch == ')'){
      if(check.empty() || check.top() == '['){
        avail = false;
        break;
      }
      check.pop();
    }
    else if(ch == ']'){
      if(check.empty() || check.top() == '('){
        avail = false;
        break;
      }
      check.pop();
    }
    else check.push(ch);
  }

  if(!avail || !check.empty()){
    cout << 0;
    return 0;
  }

  for(auto ch: str){
    if(ch == '(' || ch == '[') st.push({1, ++depth});
    else{
      pair<int, int> temp;
      
      temp.first = (ch == ')' ? 2 : 3);
      temp.second = depth;

      if(st.top().second == depth + 1){ // 만약 현재 depth 안에 다른 괄호열이 존재했을 경우, 걔가 top에 위치할 것이다. 그 값을 temp에 곱한다. 
        temp.first *= st.top().first;
        st.pop();
      }

      st.pop(); // 현재 depth의 괄호열을 열 때 push 했던 원소를 pop.

      if(!st.empty() && st.top().second == depth){ // 아직 st이 안 비었고, top 원소의 depth가 현재 depth와 같다면, 그 값을 temp에 더해준다.
        temp.first += st.top().first;
        st.pop();
      }

      st.push(temp);
      depth--;
    }
  }

  cout << st.top().first;

  return 0;
}

/*
스택 문제. 자세한 건 주석에 써놓음.
*/