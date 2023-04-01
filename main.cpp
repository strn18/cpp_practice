#include <iostream>

using namespace std;

int comb[30][30] = {0};

int combination(int n, int r){
  // return nCr

  if(comb[n][r]) return comb[n][r];

  if(n == r) return comb[n][r] = 1;
  if(r == 1) return comb[n][r] = n;

  return comb[n][r] = combination(n-1, r-1) + combination(n-1, r);
}

int main(){
  int T;

  scanf("%d", &T);

  while(T--){
    int N, M;

    scanf("%d %d", &N, &M);

    printf("%d\n", combination(M, N));
  }

  return 0;
}