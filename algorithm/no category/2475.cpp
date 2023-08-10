#include <iostream>
#include <cmath>

using namespace std;

int main(){
  int pow_sum = 0;

  for(int i=0; i<5; i++){
    int temp;
    cin >> temp;
    pow_sum += pow(temp, 2);
  }

  printf("%d", pow_sum%10);

  return 0;
}