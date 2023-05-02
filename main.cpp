#include <iostream>
#define MAX 12
#define PICK 6

using namespace std;

int k, S[MAX], num[PICK];

void choose(int n, int idx);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while(true){
    cin >> k;

    if(!k) break;

    for(int i=0; i<k; i++)
      cin >> S[i];

    choose(PICK, 0);
    cout << '\n';
  }

  return 0;
}

void choose(int n, int idx){
  if(n==0){
    for(int i=0; i<PICK; i++)
      cout << num[i] << ' ';
    cout << '\n';
    return;
  }

  for(int i=idx; i<k; i++){
    num[PICK-n] = S[i];
    choose(n-1, i+1);
  }
}