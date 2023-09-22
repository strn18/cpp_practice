#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int oddSum = 0, oddMin = 100;

  for(int i=0; i<7; i++){
    int num;

    cin >> num;

    if(num % 2 == 0) continue;

    oddSum += num;
    oddMin = min(oddMin, num);
  }
  
  if(oddSum == 0) cout << -1;
  else cout << oddSum << '\n' << oddMin;

  return 0;
}