#include <iostream>
#include <deque>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  deque<char> dq;
  string str, boom;
  int N, M;

  cin >> str;
  cin >> boom;

  N = str.size();
  M = boom.size();

  for(int i=0; i<N; i++){
    if(str[i] == boom[M-1] && dq.size() >= M-1){
      bool flag = true;

      for(int j=0; j<M-1; j++){
        if(dq[dq.size()-1-j] != boom[M-2-j]){
          flag = false;
          break;
        }
      }

      if(flag)
        for(int j=0; j<M-1; j++) 
          dq.pop_back();
      else
        dq.push_back(str[i]);
    }
    else dq.push_back(str[i]);
  }

  if(dq.empty())
    cout << "FRULA";
  else
    for(int i=0; i<dq.size(); i++)
      cout << dq[i];

  return 0;
}

/*
스택 말고 덱을 쓰긴 했는데 어쨌든 핵심 개념은 비슷하고, 알고리즘 분류도 스택으로 되어 있어서 걍 스택으로 분류했음.

가장 단순한 풀이방법은, 그냥 문자열을 앞에서부터 읽으면서 폭발 문자열을 찾고, 찾았다면 제거 후 다시 앞에서부터 찾고... 를 하는 건데, 이렇게 하면
문자열의 길이가 최대 백만이기에 시간초과가 난다(대충 O(N^2)이 나오니깐).

그래서 어떻게 할까 하다가 덱을 쓰기로 함. 문자열인 str의 맨 앞 문자부터 덱인 dq에 하나하나 push_back을 해준다. 그러다가, str의 이번 문자
(str[i])가 폭발 문자열인 boom의 마지막 문자(boom[M-1])와 같다면? 잘하면 dq의 끝의 문자들과 함께 폭발 문자열을 이루어 터질 수 있으므로
검사해준다. 25행에 있는 것처럼, dq의 M-1개의 문자와 boom의 M-1개의 문자를 대조하여 일치할 경우 걔들은 다 폭발하니깐 pop_back 해준다(36행).

만약 일치하지 않거나, 이번 문자 str[i]가 boom[M-1]가 아니라면 그냥 dq에 str[i]를 push_back 해주면 된다. 그런 다음, 마지막에는 dq에 남은 문자들
또는 FRULA를 출력한다.

첫번째 제출에서는 25행의 for문의 조건 검사 부분에서 j<M-1; 을 안 해줘서 틀렸음. 두번째, 세번째 제출도 out of bounds가 나오면서 틀렸는데, 왜그런가
하고 보니 22행에서 if문의 조건에 dq.size() >= M-1 얘를 안 넣어줬다. 이걸 안 넣어주게 되면, dq에는 아직 "aa" 밖에 없는데, boom이 "aaaa"일 때
dq의 뒤에서부터 M-1(3)개의 원소를 찾아보게 되면서 인덱스가 배열 범위를 벗어나게 됨. 이거 고치니까 맞았다.
*/