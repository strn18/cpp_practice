#include <iostream>
#define MAX 100

using namespace std;

int N, sw[MAX+1];

void change(int gender, int number);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int M, gender, number;

  cin >> N;

  for(int i=1; i<=N; i++)
    cin >> sw[i];
  
  cin >> M;

  while(M--){
    cin >> gender >> number;
    change(gender, number);
  }

  for(int i=1; i<=N; i++){
    cout << sw[i] << ' ';
    if(i % 20 == 0) cout << '\n';
  }

  return 0;
}

void change(int gender, int number){
  if(gender == 1){
    for(int i=1; i<=N; i++){
      if(i % number == 0) sw[i] = (sw[i] + 1) % 2;
    }
  }
  else{
    sw[number] = (sw[number] + 1) % 2;

    for(int i=1; (1 <= number - i) && (number + i <= N); i++){
      if(sw[number - i] == sw[number + i]){
        sw[number - i] = (sw[number - i] + 1) % 2;
        sw[number + i] = (sw[number + i] + 1) % 2;
      }
      else break;
    }
  }
}