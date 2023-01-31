#include <iostream>
#include <string>
#define MAX 10000

using namespace std;

struct Stack{
  int s[MAX];
  int size;

  void push(){
    scanf("%d", &s[size++]);
  }
  void pop(){
    if(size == 0)
      printf("-1\n");
    else
      printf("%d\n", s[(size--)-1]);
  }
  void top(){
    if(size == 0)
      printf("-1\n");
    else
      printf("%d\n", s[size-1]);
  }
};

int main(){
  int N;
  scanf("%d", &N);

  Stack st;
  st.size = 0;

  while(N--){
    string com;

    cin >> com;

    if(com == "push")
      st.push();
    else if(com == "pop")
      st.pop();
    else if(com == "size")
      printf("%d\n", st.size);
    else if(com == "empty")
      printf("%d\n", st.size == 0);
    else
      st.top();
  }

  return 0;
}