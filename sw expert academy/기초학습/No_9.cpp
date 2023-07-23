// [S/W 문제해결 기본] 9일차 - 사칙연산 유효성 검사(4. 트리)
#include <iostream>

using namespace std;

bool is_num(char ch);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  TC = 10;

  for(int t=1; t<=TC; t++){
    int N;
    bool flag = true;

    cin >> N;

    for(int i=0; i<N; i++){
      int num, left, right;
      char ch, next;

      cin >> num >> ch;

      next = cin.get();

      if(next == '\n'){
        if(!is_num(ch)) flag = false;
        continue;
      }
      else if(is_num(ch)) flag = false;

      cin >> left;

      next = cin.get();

      if(next == '\n'){
        if(!is_num(ch)) flag = false;
        continue;
      }

      cin >> right;
    }

    cout << '#' << t << ' ' << (flag ? 1 : 0) << '\n';
  }

  return 0;
}

bool is_num(char ch){
  if('0'<=ch && ch<='9') return true;
  else return false;
}

/*
No_8이랑 같은 방식으로 괜히 까다롭게 만들어 놓은 문제. 그냥 주어진 노드가 연산자인데 자식이 둘이 아닐 경우 유효하지 않아지고, 숫자인데 자식이
하나 이상일 경우 유효하지 않아지는 것만 알면 쉽게 푸는 문제인데, No_8에서 설명한대로 괜히 입력 받기 어렵게 해놓음. 그래서 그냥 No_8 코드의
입력받는 그 부분(cin.get() 사용하는) 그대로 가져와서 하니까 맞음.
*/