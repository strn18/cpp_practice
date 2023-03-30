#include <iostream>
#include <string>
#define MAX 40

using namespace std;

int messi_len[MAX+1];
string MESSI = " Messi";
string GIMOSSI = " Gimossi";

void find_messi(int n, int m);

int main(){
  int M, N;

  messi_len[0] = 7;
  messi_len[1] = 5;
  for(int i=2; i<=MAX; i++)
    messi_len[i] = messi_len[i-1]+1+messi_len[i-2];

  scanf("%d", &M);
  
  for(int i=1; i<=MAX; i++){
    if(messi_len[i] >= M){
      N = i;
      break;
    }
  }

  find_messi(N, M);

  return 0;
}

void find_messi(int n, int m){
  if(n<=1){
    printf("%c", (n==1 ? MESSI[m] : GIMOSSI[m]));
    return;
  }

  if(m <= messi_len[n-1])
    find_messi(n-1, m);
  else if(m == messi_len[n-1]+1)
    printf("Messi Messi Gimossi");
  else
    find_messi(n-2, m-(messi_len[n-1]+1));
}