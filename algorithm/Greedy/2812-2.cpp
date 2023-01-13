#include <iostream>
#include <vector>

using namespace std;

int main(){
  int N, K, num;
  vector<int> st;

  scanf("%d %d", &N, &K);

  for(int i=0; i<N; i++){
    scanf("%1d", &num);
    while(!st.empty() && st.back()<num && K){
      st.pop_back();
      K--;
    }
    st.push_back(num);
  }

  for(int i=0; i<st.size()-K; i++)
    printf("%d", st[i]);
  
  return 0;
}

/*
2812의 다른 풀이 보고, 그거대로 한 번 풀어봤다. 다만, 마지막 출력 과정에서 스택의 맨 밑부터 출력해야해서, stack 말고 벡터를 사용했다.
제출했더니 맞았음 확인
*/