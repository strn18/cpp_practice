#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int N = 1;
  long long S, sum_to_N = 1;

  cin >> S;

  while(sum_to_N <= S)
    sum_to_N += (++N);
  
  cout << N-1;

  return 0;
}