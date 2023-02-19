#include <iostream>

using namespace std;

long long pow_mod(int a, int b, int mod);

int main(){
  int A, B, C;

  scanf("%d %d %d", &A, &B, &C);

  printf("%d", pow_mod(A, B, C));
  
  return 0;
}

long long pow_mod(int a, int b, int mod){
  if(b == 0) return 1;

  if(b%2 == 0)
    return pow_mod(a, b/2, mod) * pow_mod(a, b/2, mod) % mod;
  else
    return (pow_mod(a, (b-1)/2, mod) * pow_mod(a, (b-1)/2, mod) % mod) * a % mod;
}