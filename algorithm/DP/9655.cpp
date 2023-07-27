#include <iostream>
#define MAX 1000

using namespace std;

int main(){
  int N;
  bool first_win[MAX+1];

  cin >> N;

  first_win[1] = true;
  first_win[2] = false;
  first_win[3] = true;

  for(int i=4; i<=N; i++)
    if(first_win[i-1] && first_win[i-3]) first_win[i] = false;
    else first_win[i] = true;

  cout << (first_win[N] ? "SK" : "CY");

  return 0;
}