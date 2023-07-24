#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool is_alpha(char ch);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string str;
  stack<pair<char, int>> op;
  int br = 0;

  cin >> str;

  for(int i=0; i<str.size(); i++){
    if(is_alpha(str[i])) cout << str[i];

    else if(str[i] == '+' || str[i] == '-'){
      while(!op.empty()){
        if(op.top().second < br) break;

        cout << op.top().first;
        op.pop();
      }

      op.push({str[i], br});
    }

    else if(str[i] == '*' || str[i] == '/'){
      while(!op.empty()){
        if(op.top().second < br) break;
        if((op.top().second == br) && (op.top().first == '+' || op.top().first == '-')) break;

        cout << op.top().first;
        op.pop();
      }

      op.push({str[i], br});
    }

    else if(str[i] == '(') br++;
    else br--;
  }

  while(!op.empty()){
    cout << op.top().first;
    op.pop();
  }

  return 0;
}

bool is_alpha(char ch){
  if('A' <= ch && ch <= 'Z') return true;
  else return false;
}

/*
좀 까다로웠는데, 너무 지엽적으로 생각 안 하고 문제에서 알려준 것 토대로 기본적인 것만 생각해보니 풀 수 있었던 문제.

우선 문제에서 힌트를 줬다. 주어진 연산식을 연산 순서대로 잘 괄호를 쳐줬을 때, 어떠한 ((뭉탱이1) 연산자 (뭉탱이2)) 꼴이 있다고 하자.
이때 이거를 후위 표기식으로 잘 출력하려면, 우선 뭉탱이1을 후위식으로 잘 출력해준다. 그 다음 뭉탱이2를 마찬가지로 후위식으로 출력해주고, 마지막으로
연산자를 출력해주면 된다. 

이걸 토대로 잘 생각해보니깐(그 전에는 그냥 무지성으로 풀어봤는데(첫번째 두번째 제출), 너무 복잡해지고 조건문이 지엽적으로 되어버림. 그래서 포기),
뭔가 알 수 있었음.

연산식 str을 차례대로 돈다고 하자. 

이번 str[i]가 알파벳이라면? 그냥 출력하면 된다. 

연산자라면? 스택에 넣어둔 연산자들을 top부터 살피는데, 만약 top이 지금의 나(str[i])보다 더 깊은 괄호에 묶여있었다면, 걔는 이제 괄호가 닫히고 
끝난 거니깐 걔를 출력해줘야 한다. 위의 뭉탱이 예시에서, 마지막 괄호가 닫히면 괄호 안의 모든 연산은 끝났기에, 연산자를 출력하는 것과 같은 원리임. 

만약 top보다 내가 더 깊은 괄호에 묶여있다면, top을 출력해서는 안 된다(top이 속한 가장 바깥 괄호의 연산이 안 끝났잖아). 그러므로 그냥 스택에 나를 
push해주면 된다.

만약 top과 내가 같은 깊이의 괄호에 묶여있다면, 나랑 top 사이의 연산자 우선순위를 따져봐야 한다. 내가 + or - 라면, 내가 top보다 우선순위가 빠를
일은 없으므로 top을 출력해준다. 내가 * or / 라면, top이 + or - 라면 내가 우선순위가 더 빠르니까 top을 출력하지 않고 그냥 스택에 나를 push 해준다. 
그렇지 않다면(top이 * or / 라면) top이 더 앞에 있어서 우선순위가 빠르므로 걔를 출력해준다.

이번 str[i]가 (라면 새로운 괄호가 열려서 깊이가 깊어지므로 br++ 해준다. )라면 반대로 br-- 해준다.

자세히 설명을 안 해놨는데, 코드 보면 이해가 갈 거임. op에서 first가 연산자이고 second가 걔의 괄호 깊이이다. 

참고로 유의할 점은, 76~84행의 판단을 한 번만 하는 게 아니라, while문으로 계속 해봐야 함. 내(str[i])가 op.top의 연산자보다 우선순위가 낮은 한, 
op.top을 출력해주고 pop하는 거를 계속 해야된다 이거임. 그러다가 내가 우선순위가 높아지면(또는 op가 비면), 그제서야 break하고 나를 op에 push하면 
된다.

https://donggoolosori.github.io/2020/10/19/boj-1918/ 여기 풀이를 보니깐 아예 괄호도 스택에 넣으면서 푸는 방법이 있었음. 나보다 우선순위 높지 
않은 놈이 나올 때까지 스택의 top을 계속 출력하고 pop한다는 점에서 큰 차이는 없는듯.
*/