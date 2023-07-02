#include <iostream>
#define MAX 8

using namespace std;

int N;
int num[MAX];
bool chosen[MAX+1] = {false};

void choose(int count);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N;

  choose(0);

  return 0;
}

void choose(int count){
  if(count == N){
    for(int i=0; i<N; i++)
      cout << num[i] << ' ';
    cout << '\n';
    return;
  }

  for(int i=1; i<=N; i++){
    if(chosen[i]) continue;

    num[count] = i;
    chosen[i] = true;

    choose(count + 1);

    chosen[i] = false;
  }
}