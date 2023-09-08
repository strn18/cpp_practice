#include <iostream>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, ans = 0;
  string S;

  int items = 0;
  bool prevWasI = false;

  cin >> N >> M >> S;

  for(int i=0; i<M; i++){
    if(S[i] == 'I'){
      if(prevWasI){
        items = 1;
      }
      else{
        if((++items) == 2*N + 1){
          ans++;
          items -= 2;
        }
        prevWasI = true;
      }
    }
    else{
      if(!prevWasI){
        items = 0;
      }
      else{
        items++;
        prevWasI = false;
      }
    }
  }

  cout << ans;

  return 0;
}

/*
처음에는 IOIOI.. 를 다 찾는 방식으로 했는데 최적화를 좀 해도 시간초과가 나서 50점만 맞음.

그래서 방식을 바꿨다.
문자열을 다 돌면서, 이전 문자가 I였고 이번 문자가 O라면 items++해준다. 마찬가지로 이전이 O, 이번이 I라면 items++해준다.
그러다가 items가 2*N + 1이면 P_N을 찾은거니까 ans++해준다. 이때, 가령 P_N이 IOIOI라면, 세번째 글자인 I부터 다시 탐색해보면 된다. 그러므로 
items -= 2를 해주고 위의 과정을 반복한다. 
만약 이전이 I인데 이번이 I거나, 이전이 O인데 이번이 O라면? 지금까지의 문자열은 못 쓰는 거니까 items = 0으로 초기화해준다. 근데 이때, 
이전&이번이 I라면, 이번 문자부터는 다시 세볼 수 있으므로 items = 1로 해준다. 이전 글자가 뭐였는지는 prevWasI 변수를 사용해서 따졌음.
*/