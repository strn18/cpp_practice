#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  cin >> N;

  for(int i=1; i<=N; i++){
    for(int j=0; j<N-i; j++)
      cout << ' ';
    for(int j=0; j<2*i-1; j++)
      cout << '*';
    cout << '\n';
  }

  return 0;
}