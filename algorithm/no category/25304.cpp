#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int X, N;

  cin >> X >> N;

  for(int i=0; i<N; i++){
    int a, b;

    cin >> a >> b;

    X -= a*b;
  }

  cout << (X==0 ? "Yes" : "No");

  return 0;
}