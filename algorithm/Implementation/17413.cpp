#include <iostream>
#include <string>

using namespace std;

string S;

void print(int start, int end, bool rev);
bool isAlphaNum(char ch);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  bool isWord = false, isTag = false;
  int start = 0;

  getline(cin, S);

  for(int i=0; i<S.size(); i++){
    if(isTag){
      if(S[i] == '>'){
        print(start, i, false);
        isTag = false;
      }
    }

    else if(isWord){
      if(!isAlphaNum(S[i])){
        print(start, i-1, true);
        isWord = false;

        if(S[i] == '<'){
          start = i;
          isTag = true;
        }
        else cout << ' ';
      }
    }

    else{
      if(isAlphaNum(S[i])){
        isWord = true;
        start = i;
      }
      else{
        isTag = true;
        start = i;
      }
    }
  }

  if(isWord) print(start, S.size()-1, true);
  
  return 0;
}

void print(int start, int end, bool rev){
  if(rev){
    for(int i=end; i>=start; i--)
      cout << S[i];
  }
  else{
    for(int i=start; i<=end; i++)
      cout << S[i];
  }
}

bool isAlphaNum(char ch){
  if(ch == ' ' || ch == '<' || ch == '>') return false;
  else return true;
}

/*
좀 귀찮은 문자열 + 구현 문제.

태그와 단어를 구별하면서, 각각의 시작과 끝을 찾을 때마다 출력해주도록 했다.

S[0]부터 차례대로 도는데, isWord는 현재 단어 상태인지 나타내고, isTag는 현재 태그 상태인지 나타낸다.

isTag가 true라면, >가 나올 때까지는 무시하다가, >가 나오면 print 함수로 태그의 시작(<)부터 >까지 그대로(reverse 없이) 출력한다.
isWord가 true라면, 단어의 끝, 즉 공백이나 <가 나올 때까지는 무시하다가, 끝이 나오면 그 전까지 print 함수로 순서를 반대로 출력한다.
단어나 태그의 시작이 왔다면, start = i를 해주고 isWord/isTag = true를 해준다. 

맨 마지막에는, 마지막 단어를 아직 출력 안 했을 경우 출력해준다. 

다른 풀이를 보니 스택으로 풀었다. 우선 별도의 문자열(답)과 스택을 만들어둔다. 단어라면 스택에 넣어 나중에 뺄 때 순서가 반대가 되도록 하고, 
태그라면 그대로 문자열에 넣어놓는다. 그런 다음 마지막에 그 문자열을 출력하는 방식. https://vansoft1215.tistory.com/102
*/