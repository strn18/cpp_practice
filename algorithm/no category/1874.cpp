#include <iostream>
#include <stack>
#include <queue>
#define MAX 100000

using namespace std;

int main(){
  stack<int> st, next;
  queue<char> print_q;
  int n, target;
  bool no_flag = false;

  scanf("%d", &n);
  for(int i=n+1; i>=1; i--)
    next.push(i);

  for(int i=0; i<n; i++){
    scanf("%d", &target);

    if(target >= next.top()){
      while(next.top() <= target){
        st.push(next.top());
        print_q.push('+');
        next.pop();
      }
      st.pop();
      print_q.push('-');
    }

    else{
      if(st.top() == target){
        st.pop();
        print_q.push('-');
      }
      else{
        no_flag = true;
      }
    }
  }

  if(no_flag)
    printf("NO\n");
  else{
    for(int i=0; i<n*2; i++){
      printf("%c\n", print_q.front());
      print_q.pop();
    }
  }
  
  return 0;  
}

/*
처음에는 주어지는 수열로부터 규칙을 찾아서, 가능한 경우의 불가능한 경우(NO)를 찾아야하나 싶어서 고민했었는데, 생각해보니 그냥 수열을 하나하나 
입력받으면서 입력받은 수에 따라 가능하면 push와 pop 작업을 수행하고, 불가능하면 no_flag를 세우기로 했다.
처음에는 push와 pop 수행에 따라 바로바로 +와 -를 출력하는 식으로 했는데, 문제를 잘 보니 가능할 때만 출력하고, 불가능할 때는 아예 NO만 
출력해야한다. 그래서 print_q라는 큐를 만들어서 거기에 +나 -를 넣다가, 불가능하게될 때 no_flag를 세운다. 입력이 끝난 다음, no_flag가 세워졌다면
NO를 출력하고 그렇지 않다면 print_q를 출력한다. 
가능한지 안한지 구분은, 우선 스택 st에 넣을 1~n의 오름차순 수를 next라는 스택에 미리 넣어둔다(스택이니까 넣을 때는 내림차순으로 넣어야 함).
그 다음, 입력받은 수 target이 st에 다음으로 들어올 수(=next.top())보다 크거나 같다면, st에 target까지 넣어준다. 그 다음, st에서 target을
pop해준다.
만약 target이 next.top()보다 작다면, target은 이미 st에 들어가있는 것이다. 그러므로, st.top()을 확인하고 그게 target이라면 pop하면 되고 
아니라면 no_flag를 세운다.
이때, next.top()을 확인하는 부분(21행)에서, next가 비워져있다면 오류가 발생한다. 이걸 방지하기위해 next에 1~n이 아니라 1~n+1을 넣어주었다.

나는 이렇게 짰는데, 다른 사람들 코드(https://gaeunhan.tistory.com/16)를 보니, 21행을 만족하면 target까지 수를 넣어주고, 그 다음에는 무조건
32행과 36행의 조건문을 실행한다. 즉 나는 target이 next.top() 이상일 때와 미만일 때를 나눴는데 그걸 적당히 합친 느낌.
*/