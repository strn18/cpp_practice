#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int a, b;

  cin >> a >> b;

  int small = min(a, b);
  int G, L;

  for(int i=1; i<=small; i++)
    if(a%i==0 && b%i==0)
      G = i;
      
  L = (a*b)/G;

  cout << G << '\n' << L;

  return 0;
}