#include <iostream>

using namespace std;

void star(int n, int r, int c){
  if(n==1)
    printf("*");
  else if(r/(n/3) == 1 && c/(n/3) == 1)
    printf(" ");
  else
    star(n/3, r%(n/3), c%(n/3));
}

int main(){
  int N;

  scanf("%d", &N);

  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++)
      star(N, i, j);
    printf("\n");
  }

  return 0;
}