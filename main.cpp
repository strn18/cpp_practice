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