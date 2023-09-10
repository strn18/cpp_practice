#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  double val[26];
  stack<double> st;
  string exp;

  cin >> N >> exp;

  for(int i=0; i<N; i++)
    cin >> val[i];

  for(int i=0; i<exp.size(); i++){
    if('A' <= exp[i] && exp[i] <= 'Z') st.push(val[exp[i] - 'A']);
    else{
      double num1, num2, result;

      num2 = st.top();
      st.pop();
      num1 = st.top();
      st.pop();

      switch(exp[i]){
        case '+':
          result = num1 + num2;
          break;
        case '-':
          result = num1 - num2;
          break;
        case '*':
          result = num1 * num2;
          break;
        case '/':
          result = num1 / num2;
          break;
      }

      st.push(result);
    }
  }

  cout << fixed;
  cout.precision(2);
  cout << st.top();

  return 0;
}

/*
스택 쓰면 되는 쉬운 문제.
*/