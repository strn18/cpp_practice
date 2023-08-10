#include <iostream>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string S;
  int i;

  cin >> S >> i;

  cout << S[i-1];

  return 0;
}