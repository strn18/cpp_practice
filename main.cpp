#include <iostream>

using namespace std;

int main(){
  long long total = 0;

  for(int i=1; i<=1000000; i++){
    total += 1000000/i;
  }

  cout << total;

  return 0;
}