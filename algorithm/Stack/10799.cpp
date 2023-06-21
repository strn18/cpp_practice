#include <iostream>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int cur_sticks = 0, total = 0;
  char prev;
  string str;

  cin >> str;

  prev = str[0];

  for(int i=1; i<str.size(); i++){
    if(prev == '(' && str[i] == '('){
      cur_sticks++;
      total++;
    }
    else if(prev == '(' && str[i] == ')')
      total += cur_sticks;
    else if(prev == ')' && str[i] == ')')
      cur_sticks--;

    prev = str[i];
  }

  cout << total;

  return 0;
}

/*
스택을 안 쓰긴 했는데 스택 같은 문제라 일단 분류는 스택으로 함.

레이저를 한 번 쏠 때마다, 쌓여 있는 막대기의 개수만큼 총 막대기 개수가 늘어난다(23행). 그리고 막대기 하나가 새로 추가될 때마다 총 막대기 개수도
1씩 늘어남(19행). 이를 위해 쌓여 있는 막대기(레이저가 닿을)의 개수를 cur_sticks, 총 막대기 개수를 total로 했음.
*/