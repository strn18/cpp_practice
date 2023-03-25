#include <iostream>
#include <stack>

using namespace std;

int main(){
  int K, n;
  long long total = 0;
  stack<int> st;

  scanf("%d", &K);

  for(int i=0; i<K; i++){
    scanf("%d", &n);

    if(!n)
      st.pop();
    else
      st.push(n);
  }

  while(!st.empty()){
    total += st.top();
    st.pop();
  }

  printf("%lld", total);

  return 0;
}