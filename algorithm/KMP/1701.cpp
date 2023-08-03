#include <iostream>
#include <string>
#define MAX 5000

using namespace std;

int fail[MAX];

int max_fail(string s); // s의 fail 함수의 값 중 최댓값을 return.

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string str;
  int ans = 0;

  cin >> str;

  for(int i=0; i<str.length(); i++)
    ans = max(ans, max_fail(str.substr(i, str.length()-i)));

  cout << ans;

  return 0;
}

int max_fail(string s){
  int M = s.length(), ans = 0;

  for(int i=0; i<M; i++) fail[i] = 0;

  for(int i=1, j=0; i<M; i++){
    while(j > 0 && s[i] != s[j]) j = fail[j-1];

    if(s[i] == s[j]){
      fail[i] = j+1;
      ans = max(ans, fail[i]);
      j++;
    }
  }

  return ans;
}

/*
백준에서 처음 풀어본 KMP 문제. 처음에는, 모든 부분 문자열을 찾고 그걸 갖고 KMP를 쳐서, 그 결과 true가 리턴된다면(그 부분 문자열을 하나라도 찾는 데 
성공했다면), 해당 길이가 정답이 되는 것으로 짰다(이때, 부분 문자열은 길이가 N-1, N-2, ..., 1 이렇게 감소하는 순서로 하였음). 그랬더니 시간초과가 
났다(첫번째 제출). 그래서 생각해보니깐, 모든 부분 문자열은 약 N^2개인데, KMP도 약 O(N) 정도니까 시간초과가 안 날리가 없다... 왜 된다고 생각했지?

어쨌든 고민하다가 모르겠어서 https://restudycafe.tistory.com/410 여기를 살짝 훑어봄. 그랬더니 fail 함수 만드는 걸 이용하라는 걸 봤는데, 
생각해보니 주어진 문자열 str에서 어떠한 별개의 문자열을 찾는 게 아니라, str에서 str의 어떠한 부분 문자열을 찾는 것이다. 그리고, fail 함수는 
어떠한 문자열에 s에 대해서, s[0]~s[i]라는 부분 문자열에서 일치하는 접두사와 접미사의 길이를 의미한다. 이를 이용한다면? 
str에 대해서 fail 함수 만드는 것을 해보자. 그러면, fail[i]에는 str[0]~str[i]의 일치하는 접두사와 접미사의 길이가 담긴다. 이를 이용하여, 
str[0~N-1](N은 str의 길이), str[1~N-1], ..., str[N-1~N-1]에 대해서 fail 함수 만들기를 친다면(20~21행), 원하는 답을 구할 수 있다.

글로 설명하니까 좀 어려운데, 머릿속에 그려보면서 생각해보면 쉬움. 정 모르겠으면 memos 그림 참조 ㄱㄱ
*/