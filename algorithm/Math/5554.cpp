#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int total = 0;

  for(int i=0; i<4; i++){
    int n;
    cin >> n;
    total += n;
  }

  cout << (total / 60) << '\n' << (total % 60);

  return 0;
}