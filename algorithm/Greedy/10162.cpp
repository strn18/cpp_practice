#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T, count = 0;
  int buttonTime[3] = {300, 60, 10}, buttonPush[3] = {0};

  cin >> T;

  if(T % 10){
    cout << -1;
    return 0;
  }

  for(int i=0; i<3; i++){
    if(T < buttonTime[i]) continue;

    buttonPush[i] = (T / buttonTime[i]);
    T %= buttonTime[i];
  }

  for(int i=0; i<3; i++)
    cout << buttonPush[i] << ' ';

  return 0;
}

/*
기초 그리디 문제. 
*/