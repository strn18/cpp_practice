#include <iostream>
#include <string>
#define MAX 50

using namespace std;

int N, K, ans = 0;
int antic[5] = {0, 13, 19, 8, 2};

int word[MAX] = {0}; // bitmasking
int exist = 0, chose = 0; // bitmasking

void combination(int cur, int count);
bool is_antic(int n);
void count_words(void);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string temp;

  cin >> N >> K;

  for(int i=0; i<N; i++){
    cin >> temp;

    for(int j=4; j<temp.size()-4; j++){
      word[i] |= (1 << temp[j]-'a');
      exist |= (1 << temp[j]-'a');
    }
  }

  if((K -= 5) < 0){
    cout << 0;
    return 0;
  }

  for(int i=0; i<5; i++)
    chose |= (1 << antic[i]);
  
  combination(1, 0);

  cout << ans;

  return 0;
}

void combination(int cur, int count){
  if(cur == 26 || count == K){
    count_words();
    return;
  }

  if(is_antic(cur) || !(exist & (1 << cur)) )
    combination(cur+1, count);
  else{
    chose |= (1 << cur);
    combination(cur+1, count+1);

    chose &= ~(1 << cur);
    combination(cur+1, count);
  }
}

bool is_antic(int n){
  for(int i=0; i<5; i++)
    if(n == antic[i]) return true;
  return false;
}

void count_words(void){
  int count = 0;

  for(int i=0; i<N; i++)
    if((chose & word[i]) == word[i]) count++;

  ans = max(ans, count);
}

/*
순열(백트래킹) + 브루트포스 + 비트마스킹 문제.

예전에 파이썬으로 풀었던 건데 C++로도 풀어봤다. 처음에 풀 때는 비트마스킹 없이 걍 풀었었는데, 풀고 난 다음
https://nanyoungkim.tistory.com/173 여기 글 보면서 비트마스킹으로 다시 풀어봤다.
*/